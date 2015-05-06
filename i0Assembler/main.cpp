#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdint>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <memory>
#include <cassert>
#include <algorithm>
#include "../../../d-thinker/l0-bin-translator/src/codec.h"
#include "../../../d-thinker/l0-bin-translator/src/external/sys_config.h"

#define I0_INS_LEN_CONV		(0x04U)
#define I0_INS_LEN_ALU		(0x03U)
#define I0_INS_LEN_SPAWN	(0x03U)
#define I0_INS_LEN_SPAWNX	(0x04U)
#define I0_INS_LEN_EXIT		(0x02U)
#define I0_INS_LEN_BIJ		(0x03U)
#define I0_INS_LEN_BJ		(0x02U)
#define I0_INS_LEN_BCMP		(0x04U)
#define I0_INS_LEN_BZNZ		(0x03U)
#define I0_INS_LEN_NOP		(0x02U)
#define I0_INS_LEN_INT		(0x02U)
#define I0_INS_LEN_SHIFT	(0x04U)
#define I0_INS_LEN_STR		(0x04U)
#define I0_INS_LEN_SCMP		(0x04U)
#define I0_INS_LEN_OPCODE	(0x02U)
#define I0_INS_LEN_BOPCODE	(0x02U)

typedef std::vector<unsigned char> inst_vector;
typedef std::map<size_t, std::string> symref;
typedef std::map<std::string, size_t> symdef;
typedef void
encode_inst(const std::string&, std::istream&, inst_vector&, symref&);
typedef std::map<const std::string, encode_inst> encoder_map;

template<size_t N>
void serialize_opcode(const unsigned char (&b)[N], inst_vector& out)
{
	for (auto i = N; i > 0; --i)
	{
		out.push_back(b[i - 1]);
	}
}
template<typename T>
void serialize_int(T b, inst_vector& out)
{
	for (auto i = (unsigned char*) &b; i != (unsigned char*) (&b + 1); ++i)
	{
		out.push_back(*i);
	}
}

namespace i0spec
{
enum i0regs
{
	r0, r1, r2, r3, r4, lr, sp, bp,
};
}

struct i0D
{
	virtual void
	serialize(inst_vector&) const =0;
	virtual unsigned
	addrm() const=0;
	virtual inline ~i0D()
	{
	}
};

struct i0I: i0D
{
	inline i0I(const char* _data) :
			data(std::stoll(_data))
	{
	}
	const int64_t data;
	virtual inline void serialize(inst_vector& bytes) const
	{
		serialize_int(data, bytes);
	}
	virtual inline unsigned addrm() const
	{
		return ADDRM_IMMEDIATE;
	}
};

i0spec::i0regs decode_reg(const char* reg)
{
	const static std::map<std::string, i0spec::i0regs> reg_map =
	{
	{ "r0q", i0spec::r0 },
	{ "r1q", i0spec::r1 },
	{ "r2q", i0spec::r2 },
	{ "r3q", i0spec::r3 },
	{ "r4q", i0spec::r4 },
	{ "lrq", i0spec::lr },
	{ "spq", i0spec::sp },
	{ "bpq", i0spec::bp }, };
	auto i = reg_map.find(reg);
	if (i == reg_map.end())
	{
		throw std::runtime_error("invalid reg");
	}
	return i->second;
}

struct i0R: i0D
{
	inline i0R(const char* _reg) :
			reg(decode_reg(_reg))
	{
	}
	virtual inline unsigned addrm() const
	{
		return ADDRM_ABSOLUTE;
	}
	const i0spec::i0regs reg;
	virtual inline void serialize(inst_vector& bytes) const
	{
		uint64_t regfile = REG_FILE_BEGIN + sizeof(uint64_t) * reg;
		serialize_int(regfile, bytes);
	}
};

struct i0M: i0R
{
	inline i0M(const char* _reg, const char* _offset) :
			i0R(_reg), offset(std::stol(_offset))
	{
	}
	virtual inline unsigned addrm() const
	{
		return ADDRM_DISPLACEMENT;
	}
	const int32_t offset;
	virtual inline void serialize(inst_vector& bytes) const
	{
		serialize_int(offset, bytes);
		i0R::serialize(bytes);
	}
};

struct i0S: i0D
{
	std::string sym;
	symref& refs;
	inline i0S(const char* _sym, symref& _refs) :
			sym(_sym), refs(_refs)
	{
	}
	virtual inline unsigned addrm() const
	{
		return ADDRM_IMMEDIATE;
	}
	virtual inline void serialize(inst_vector& bytes) const
	{
		refs.insert(std::make_pair(bytes.size(), std::move(sym)));
		serialize_int(0xBADDF00DBADDF00DULL, bytes);
	}
};

std::string&
check_inner_oper(std::string& oper)
{
	if (oper.size())
	{
		if (oper.back() == ',')
		{
			oper.pop_back();
			return oper;
		}
	}
	throw std::runtime_error("invalid operand");
}

typedef std::unique_ptr<i0D> i0oper;

i0oper get_oper(std::string& oper, symref& symrefmap)
{
	if (oper.size())
	{
		if (oper.front() == '$')
		{
			return i0oper(new i0I(oper.c_str() + 1));
		}
		else if (oper.front() == '(')
		{
			auto i = oper.rfind(')');
			if (i != std::string::npos)
			{
				oper[i] = '\0';
				return i0oper(new i0M(oper.c_str() + 1, oper.c_str() + i + 1));
			}
		}
		else if (oper.front() == '@')
		{
			return i0oper(new i0S(oper.c_str() + 1, symrefmap));
		}
		else
		{
			return i0oper(new i0R(oper.c_str()));
		}
	}
	throw std::runtime_error("invalid operand");
}

union i0ADDM
{
	struct
	{
		uint32_t addrm3 :3;
		uint32_t addrm2 :3;
		uint32_t addrm1 :3;
		uint32_t A :4;
		uint32_t opcode :11;
	};
	unsigned char b[I0_INS_LEN_ALU];
} bytes;

union i0AADM
{
	struct
	{
		uint32_t :7;
		uint32_t addrm2 :3;
		uint32_t addrm1 :3;
		uint32_t A2 :4;
		uint32_t A1 :4;
		uint32_t opcode :11;
	};
	unsigned char b[I0_INS_LEN_CONV];
};

union i0AAT
{
	struct
	{
		uint32_t :6;
		uint32_t ra :1;
		uint32_t addrm2 :3;
		uint32_t addrm1 :3;
		uint32_t A :4;
		uint32_t mode :4;
		uint32_t opcode :11;
	};
	unsigned char b[I0_INS_LEN_BCMP];
};

union i0T
{
	struct
	{
		uint32_t ra :1;
		uint32_t mode :4;
		uint32_t opcode :11;
	};
	unsigned char b[I0_INS_LEN_BJ];
};

union i0ATI
{
	struct
	{
		uint32_t :6;
		uint32_t addrm :3;
		uint32_t mode :4;
		uint32_t opcode :11;
	};
	unsigned char b[I0_INS_LEN_BIJ];
};

void encode_arithlogic(const std::string& op, std::istream& in,
		inst_vector& out, symref& refs)
{
	i0ADDM bytes
	{ };
	static const std::map<const std::string, std::pair<unsigned, unsigned> > opcode_map =
	{
	{ "add",
	{ OP_ADD, ATTR_UE } },
	{ "sub",
	{ OP_SUB, ATTR_UE } },
	{ "mul",
	{ OP_MUL, ATTR_UE } },
	{ "and",
	{ OP_AND, ATTR_UE } },
	{ "or",
	{ OP_OR, ATTR_UE } },
	{ "xor",
	{ OP_XOR, ATTR_UE } },
	{ "udiv",
	{ OP_DIV, ATTR_UE } },
	{ "sdiv",
	{ OP_DIV, ATTR_SE } } };
	auto i = opcode_map.find(op);
	if (i == opcode_map.end())
	{
		throw std::runtime_error("arithlogic opcode not found");
	}
	std::string src1, src2, dest;
	in >> src1 >> src2 >> dest;
	i0oper oper1(get_oper(check_inner_oper(src1), refs)), oper2(
			get_oper(check_inner_oper(src2), refs)), oper3(
			get_oper(dest, refs));
	assert(dynamic_cast<i0I*>(oper1.get()) || dynamic_cast<i0R*>(oper1.get()));
	assert(dynamic_cast<i0I*>(oper2.get()) || dynamic_cast<i0R*>(oper2.get()));
	assert(dynamic_cast<i0R*>(oper3.get()));
	bytes.opcode = i->second.first;
	bytes.A = i->second.second;
	bytes.addrm1 = oper1->addrm();
	bytes.addrm2 = oper2->addrm();
	bytes.addrm3 = oper3->addrm();
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
	oper2->serialize(out);
	oper3->serialize(out);
}

void encode_move(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0AADM bytes
	{ };
	std::string src, dest;
	in >> src >> dest;
	i0oper oper1(get_oper(check_inner_oper(src), refs)), oper2(
			get_oper(dest, refs));
	assert(dynamic_cast<i0I*>(oper1.get()) || dynamic_cast<i0R*>(oper1.get()));
	assert(dynamic_cast<i0R*>(oper2.get()));
	bytes.opcode = OP_CONV;
	bytes.A1 = ATTR_UE;
	bytes.A2 = ATTR_UE;
	bytes.addrm1 = oper1->addrm();
	bytes.addrm2 = oper2->addrm();
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
	oper2->serialize(out);
}

void encode_load(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0AADM bytes
	{ };
	static const std::map<std::string, std::pair<unsigned, unsigned>> ld_attr =
	{
	{ "loadrs8",
	{ ATTR_SB, ATTR_SE } },
	{ "loadrs32",
	{ ATTR_SF, ATTR_SE } },
	{ "loadrz8",
	{ ATTR_UB, ATTR_UE } },
	{ "loadrz32",
	{ ATTR_UF, ATTR_UE } },
	{ "loadra8",
	{ ATTR_SB, ATTR_SE } },
	{ "loadra32",
	{ ATTR_SF, ATTR_SE } },
	{ "loadr64",
	{ ATTR_UE, ATTR_UE } } };
	auto i = ld_attr.find(op);
	if (i == ld_attr.end())
	{
		throw std::runtime_error("load instr invalid");
	}
	std::string src, dest;
	in >> dest >> src;
	i0oper oper1(get_oper(check_inner_oper(dest), refs)), oper2(
			get_oper(src, refs));
	assert(dynamic_cast<i0M*>(oper1.get()));
	assert(dynamic_cast<i0R*>(oper2.get()));
	bytes.opcode = OP_CONV;
	bytes.A1 = i->second.first;
	bytes.A2 = i->second.second;
	bytes.addrm1 = oper1->addrm();
	bytes.addrm2 = oper2->addrm();
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
	oper2->serialize(out);
}

void encode_store(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0AADM bytes
	{ };
	static const std::map<std::string, unsigned> st_attr =
	{
	{ "storer8", ATTR_UB },
	{ "storer32", ATTR_UF },
	{ "storer64", ATTR_UE },
	{ "storei8", ATTR_UB },
	{ "storei32", ATTR_UF },
	{ "storei64", ATTR_UE } };
	auto i = st_attr.find(op);
	if (i == st_attr.end())
	{
		throw std::runtime_error("load instr invalid");
	}
	std::string src, dest;
	in >> src >> dest;
	i0oper oper1(get_oper(check_inner_oper(src), refs)), oper2(
			get_oper(dest, refs));
	assert(dynamic_cast<i0R*>(oper1.get()) || dynamic_cast<i0I*>(oper1.get()));
	assert(dynamic_cast<i0M*>(oper2.get()));
	bytes.opcode = OP_CONV;
	bytes.A1 = ATTR_UE;
	bytes.A2 = i->second;
	bytes.addrm1 = oper1->addrm();
	bytes.addrm2 = oper2->addrm();
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
	oper2->serialize(out);
}

void encode_jmp(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0T bytes
	{ };
	std::string target;
	in >> target;
	i0oper oper1(get_oper(target, refs));
	assert(dynamic_cast<i0S*>(oper1.get()));
	bytes.opcode = OP_B;
	bytes.mode = OPT_B_J;
	bytes.ra = JUMP_R;
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
}

void encode_indrjmp(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0ATI bytes
	{ };
	std::string target;
	in >> target;
	i0oper oper1(get_oper(target, refs));
	assert(dynamic_cast<i0R*>(oper1.get()));
	bytes.opcode = OP_B;
	bytes.mode = OPT_B_IJ;
	bytes.addrm = oper1->addrm();
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
}

void encode_bcc(const std::string& op, std::istream& in, inst_vector& out,
		symref& refs)
{
	i0AAT bytes
	{ };
	static const std::map<std::string,
			std::pair<bool, std::pair<unsigned, unsigned>>>bcc_attr =
	{
		{	"ble",
			{	false,
				{	OPT_B_LE, ATTR_SE}}},
		{	"bge",
			{
				true,
				{	OPT_B_LE, ATTR_SE}}},
		{	"beq",
			{	false ,
				{	OPT_B_E, ATTR_SE}}},
		{	"blt",
			{	false,
				{	OPT_B_L, ATTR_SE}}},
		{	"bgt",
			{	true,
				{	OPT_B_L, ATTR_SE}}},
		{	"bne",
			{	false,
				{	OPT_B_NE, ATTR_SE}}},
		{	"bule",
			{	false,
				{	OPT_B_LE, ATTR_UE}}},
		{	"buge",
			{	true,
				{	OPT_B_LE, ATTR_UE}}},
		{	"bueq",
			{	false,
				{	OPT_B_E, ATTR_UE}}},
		{	"bult",
			{	false,
				{	OPT_B_L, ATTR_UE}}},
		{	"bugt",
			{	true,
				{	OPT_B_L, ATTR_UE}}},
		{	"bune",
			{	false,
				{	OPT_B_NE, ATTR_UE}}}};
	auto i = bcc_attr.find(op);
	if (i == bcc_attr.end())
	{
		throw std::runtime_error("bcc invalid");
	}
	std::string src1, src2, target;
	std::string* dis_src1 = i->second.first ? &src2 : &src1;
	std::string* dis_src2 = i->second.first ? &src1 : &src2;
	in >> *dis_src1 >> *dis_src2 >> target;
	i0oper oper1(get_oper(check_inner_oper(src1), refs)), oper2(
			get_oper(check_inner_oper(src2), refs)), oper3(
			get_oper(target, refs));
	assert(dynamic_cast<i0I*>(oper1.get()) || dynamic_cast<i0R*>(oper1.get()));
	assert(dynamic_cast<i0I*>(oper2.get()) || dynamic_cast<i0R*>(oper2.get()));
	assert(dynamic_cast<i0S*>(oper3.get()));
	bytes.opcode = OP_B;
	bytes.mode = i->second.second.first;
	bytes.A = i->second.second.second;
	bytes.addrm1 = oper1->addrm();
	bytes.addrm2 = oper2->addrm();
	bytes.ra = JUMP_R;
	serialize_opcode(bytes.b, out);
	oper1->serialize(out);
	oper2->serialize(out);
	oper3->serialize(out);
}

void symfix(inst_vector& bytes, const symref& refs, const symdef& defs)
{
	for (auto i = refs.begin(), j = refs.end(); i != j; ++i)
	{
		uint64_t orig;
		std::copy(&bytes[i->first], &bytes[i->first + sizeof(uint64_t)],
				(unsigned char*) &orig);
		assert(orig == 0xBADDF00DBADDF00DULL);
		auto k = defs.find(i->second);
		if (k == defs.end())
		{
			throw std::runtime_error("symbol not found");
		}
		uint64_t update = k->second - i->first - sizeof(uint64_t);
		std::copy((unsigned char*) &update, (unsigned char*) (&update + 1),
				&bytes[i->first]);
	}
}

void emitinst(const std::string& token,std::ifstream& in, inst_vector& bytes, symdef& defs,
		symref& refs)
{

}

void dispatch( std::ifstream& in, inst_vector& bytes,
		symdef& defs, symref& refs)
{
	for (;;)
	{
		std::string token;
		in >> token;
		if (in.eof())
		{
			break;
		}
		assert(token.size());
		if(function_level.size()){
			emitfunction(token, in, bytes, defs, refs);
		}

		if (token.front() == '.')
		{
			if (token == ".proc")
			{

			}
			else if (input == ".i0_asm")
			{
				std::cerr << "beginning parsing i0 asm\n";
			}
			else
			{
				std::string unknown_directive;
				getline(in, unknown_directive);
				std::cerr << "ignoring " << unknown_directive << "\n";
			}
		}
		else if (token.front() == "#")
		{
			//eat the comment
			std::string comment;
			getline(in, comment);
		}
	}

}

int main(int argc, char** argv)
{
	if (argc != 1)
	{
		std::cerr << "invalid argument\n";
	}

	std::ifstream file(argv[1]);
	inst_vector bytes;
	symdef defs;
	symref refs;

	dispatch(input, file, bytes, defs, refs);

	return 0;
}
