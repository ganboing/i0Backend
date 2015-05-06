#include "i0InstPrinter.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {

#include "i0GenAsmWriter.inc"

i0InstPrinter::i0InstPrinter(const MCAsmInfo &mai, const MCInstrInfo &mii,
		const MCRegisterInfo &mri) :
		MCInstPrinter(mai, mii, mri) {
}

void i0InstPrinter::printInst(const MCInst *MI, raw_ostream &O,
		StringRef Annot) {
	printInstruction(MI, O);
	//printAnnotation(O, Annot);
}

static const char* expr_kind_str(MCExpr::ExprKind kind){
	switch(kind){
	case MCExpr::Binary:
		return "Binary";
	case MCExpr::Constant:
		return "Constant";
	case MCExpr::SymbolRef:
		return "SymRef";
	case MCExpr::Target:
		return "Target";
	case MCExpr::Unary:
		return "Unary";
	default:
		return nullptr;
	}
}

static void print_expr(const MCExpr* expr, raw_ostream& O){
	switch(expr->getKind()){
	case MCExpr::SymbolRef:
	{
		const MCSymbolRefExpr* symref = cast<MCSymbolRefExpr>(expr);
		O << "@" << symref->getSymbol();
		break;
	}
	default:
		llvm_unreachable("MCExpr printer not implemented");
	}
}

void i0InstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
		raw_ostream &O) {
	const MCOperand &Op = MI->getOperand(OpNo);
	if (Op.isReg()) {
		O << getRegisterName(Op.getReg());
	} else if (Op.isImm()) {
		O << Op.getImm();
	} else if (Op.isExpr()) {
		print_expr(Op.getExpr(), O);
	} else {
		llvm_unreachable("MCOperand type not handled");
	}

}

void i0InstPrinter::printImm8(const MCInst* MI, unsigned opNum, raw_ostream &O){
	O << "$";
	printOperand(MI, opNum, O);
}

void i0InstPrinter::printImm32(const MCInst* MI, unsigned opNum, raw_ostream &O){
	O << "$";
	printOperand(MI, opNum, O);
}

void i0InstPrinter::printImm64(const MCInst* MI, unsigned opNum, raw_ostream &O){
	O << "$";
	printOperand(MI, opNum, O);
}

void i0InstPrinter::printMemOperand(const MCInst *MI, int opNum,
		raw_ostream &O) {
	O << "(";
	printOperand(MI, opNum, O);
	O << ")";
	printOperand(MI, opNum + 1, O);
}

}
