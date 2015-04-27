#include "i0InstPrinter.h"
#include "llvm/MC/MCInst.h"
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
	printAnnotation(O, Annot);
}

void i0InstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
		raw_ostream &O) {
	const MCOperand &Op = MI->getOperand(OpNo);
	if (Op.isReg()) {
		O << getRegisterName(Op.getReg());
	} else if (Op.isImm()) {
		O << Op.getImm();
	} else if (Op.isExpr()) {
		O << "<expr to print>\n";
	}

}

void i0InstPrinter::printMemOperand(const MCInst *MI, int opNum,
		raw_ostream &O) {
	O << "( ";
	printOperand(MI, opNum, O);
	O << " + ";
	printOperand(MI, opNum + 1, O);
	O << ")";
}

}
