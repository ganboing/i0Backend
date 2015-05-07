class Attr<bits<4> val>{
  bits<4> Value = val;
}

class Addrm<bits<3> val>{
  bits<3> Value = val;
}

def AttrB : Attr<0>;
def AttrE : Attr<1>;
def AttrS : Attr<2>;
def AttrF : Attr<3>;

//def AttrUB : Attr<4>;
//def AttrUE : Attr<5>;
//def AttrUS : Attr<6>;
//def AttrUF : Attr<7>;

def AttrFS : Attr<8>;
def AttrFD : Attr<9>;

def AddrmImm : Addrm<0>;
def AddrmReg : Addrm<1>;
def AddrmIndr : Addrm<2>;
def AddrmDisp : Addrm<3>;

class i0Inst<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> 

: Instruction{

  bits<11> Opcode;
  let Namespace = "i0";
  let OutOperandList = outs;
  let InOperandList = ins;
  
  let AsmString = asmstr;
  let Pattern = pattern;
  let Itinerary = itin;

  let DecoderNamespace = "i0";
}

class i0Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
: i0Inst<outs, ins, asmstr, pattern, NoItinerary>
{
  let isCodeGenOnly = 1;
  let isPseudo = 1;
}


class i0InsBranch<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0Inst<outs, ins, asmstr, pattern, itin>
{
  bits<4> JOpt;
  let Opcode = 0x15;
}

class i0InsBranchCC<bits<4> jopt, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranch<outs, ins, asmstr, pattern, itin>
{
  let JOpt = jopt;
  Attr A;
  Addrm addrm1;
  Addrm addrm2;
  bits<64> jmptarget;
  let isBranch = 1;
  let isTerminator = 1;
}

class i0InsBCCri64<bits<4> jopt, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranchCC<jopt, outs, ins, asmstr, pattern, itin>
{
  let A = AttrE;
  let addrm1 = AddrmReg;
  let addrm2 = AddrmImm;
  bits<3> reg;
  bits<64> imm64;
}

class i0InsBCCir64<bits<4> jopt, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranchCC<jopt, outs, ins, asmstr, pattern, itin>
{
  let A = AttrE;
  let addrm1 = AddrmImm;
  let addrm2 = AddrmReg;
  bits<64> imm64;
  bits<3> reg;
}

class i0InsBCCrr64<bits<4> jopt, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranchCC<jopt, outs, ins, asmstr, pattern, itin>
{
  let A = AttrE;
  let addrm1 = AddrmReg;
  let addrm2 = AddrmReg;
  bits<3> reg1;
  bits<3> reg2;
}

class i0InsJmpCall<bits<4> jopt, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranch<outs, ins, asmstr, pattern, itin>
{
  bits<64> jmptarget;
}

class i0InsJmp<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsJmpCall<0x00, outs, ins, asmstr, pattern, itin> {

  let isBranch = 1;
  let isTerminator = 1;
  let isBarrier = 1;
}

class i0InsCall<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsJmpCall<0x01, outs, ins, asmstr, pattern, itin> {
  
  let isCall = 1;
}

class i0InsJmpIndir<dag out, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsBranch<out, ins, asmstr, pattern, itin>
{
  let JOpt = 0x0c;
  Addrm addrm;
}

class i0InsIndrBrR<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsJmpIndir<outs, ins, asmstr, pattern, itin>
{
  let addrm = AddrmReg;
  bits<3> reg;
  let isTerminator = 1;
  let isBarrier = 1;
}

class i0InsADDM<bits<11> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0Inst<outs, ins, asmstr, pattern, itin>
{
  Attr A;
  Addrm addrm1;
  Addrm addrm2;
  Addrm addrm3;
  
  let Opcode = op;
}

class i0InsAADM<bits<11> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0Inst<outs, ins, asmstr, pattern, itin>
{
  Attr A1;
  Attr A2;
  Addrm addrm1;
  Addrm addrm2; 
  let Opcode = op;
}

class i0InsMov64ir<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x21, outs, ins, asmstr, pattern, itin>
{
  let A1 = AttrE;
  let A2 = AttrE;
  let addrm1 = AddrmImm;
  let addrm2 = AddrmReg;
  bits<64> imm64;
  bits<3> reg;
}

class i0InsMov64rr<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x21, outs, ins, asmstr, pattern, itin>
{
  bits<3> rin;
  bits<3> rout;
  let A1 = AttrE;
  let A2 = AttrE;
  let addrm1 = AddrmReg;
  let addrm2 = AddrmReg;
}

class i0InsLoadR64Disp<Attr attr, bits<2> extmode, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x22, outs, ins, asmstr, pattern, itin>
{
  bits<3> rvalue;
  bits<3> rbase;
  bits<32> offset;
  bits<2> extMode;
  let extMode = extmode;
  let A1 = attr;
  let A2 = AttrE;
  let addrm1 = AddrmDisp;
  let addrm2 = AddrmReg;
}

class i0InsLoadR64Indr<Attr attr, bits<2> extmode, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x22, outs, ins, asmstr, pattern, itin>
{
  bits<3> rvalue;
  bits<64> addr;
  bits<2> extmode;
  let extmode = extmode;
  let A1 = attr;
  let A2 = AttrE;
  let addrm1 = AddrmIndr;
  let addrm2 = AddrmReg;
}

class i0InsStoreR64<Attr attr, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x23, outs, ins, asmstr, pattern, itin>
{
  bits<3> rvalue;
  bits<3> rbase;
  bits<32> offset;
  let A1 = AttrE;
  let A2 = attr;
  let addrm2 = AddrmDisp;
  let addrm1 = AddrmReg;
}

class i0InsStoreI64<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x23, outs, ins, asmstr, pattern, itin>
{
  bits<64> imm64;
  let A1 = AttrE;
  let A2 = AttrE;
  let addrm2 = AddrmDisp;
  let addrm1 = AddrmImm;
}

class i0InsStoreI32<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x23, outs, ins, asmstr, pattern, itin>
{
  bits<32> imm32;
  let A1 = AttrF;
  let A2 = AttrF;
  let addrm2 = AddrmDisp;
  let addrm1 = AddrmImm;
}

class i0InsStoreI8<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsAADM<0x23, outs, ins, asmstr, pattern, itin>
{
  bits<8> imm8;
  let A1 = AttrB;
  let A2 = AttrB;
  let addrm2 = AddrmDisp;
  let addrm1 = AddrmImm;
}

class i0InsAri64rrr<bits<11> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsADDM<op, outs, ins, asmstr, pattern, itin>
{
  bits<3> rb;
  bits<3> rc;
  bits<3> ra;
  
  let A = AttrE;
  let addrm1 = AddrmReg;
  let addrm2 = AddrmReg;
  let addrm3 = AddrmReg;
}

class i0InsAri64rir<bits<11> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsADDM<op, outs, ins, asmstr, pattern, itin>
{
  bits<3> rin;
  bits<64> imm64;
  bits<3> rout;

  let A = AttrE;
  let addrm1 = AddrmReg;
  let addrm2 = AddrmImm;
  let addrm3 = AddrmReg;
}

class i0InsAri64irr<bits<11> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin>
: i0InsADDM<op, outs, ins, asmstr, pattern, itin>
{
  bits<64> imm64;
  bits<3> rin;
  bits<3> rout;
  
  let A = AttrE;
  let addrm1 = AddrmImm;
  let addrm2 = AddrmReg;
  let addrm3 = AddrmReg;
}

