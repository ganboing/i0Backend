#ifndef LIB_TARGET_I0_INSTPRINTER_I0INSTPRINTER_H_
#define LIB_TARGET_I0_INSTPRINTER_I0INSTPRINTER_H_

#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class i0InstPrinter: public MCInstPrinter {
public:
	i0InstPrinter(const MCAsmInfo &mai, const MCInstrInfo &mii,
			const MCRegisterInfo &mri);
	void printInstruction(const MCInst *MI, raw_ostream &O);
	void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot) override;
private:
	const char *getRegisterName(unsigned RegNo);
	void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
	void printImm8(const MCInst* MI, unsigned OpNo, raw_ostream &O);
	void printImm32(const MCInst* MI, unsigned OpNo, raw_ostream &O);
	void printImm64(const MCInst* MI, unsigned OpNo, raw_ostream &O);
	void printMemOperand(const MCInst *MI, int opNum, raw_ostream &O);

};

}

#endif /* LIB_TARGET_I0_INSTPRINTER_I0INSTPRINTER_H_ */
