#ifndef LIB_TARGET_I0_I0ASMPRINTER_H_
#define LIB_TARGET_I0_I0ASMPRINTER_H_

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"

namespace llvm {

class i0FunctionInfo;

class i0AsmPrinter: public AsmPrinter {
	MCInst lowerToMcinst(const MachineInstr& MCI);
	MCOperand lowerToMcop(const MachineOperand& MCOP);
	i0FunctionInfo* i0FI;
	MCContext* MCcxt;
public:
	i0AsmPrinter(TargetMachine& TM, MCStreamer& Streamer);

	virtual const char *getPassName() const {
		return "i0 Assembly Printer";
	}
	virtual bool runOnMachineFunction(MachineFunction &MF);

	void EmitStartOfAsmFile(Module& M) override;
	void EmitFunctionEntryLabel() override;
	void EmitFunctionBodyStart() override;
	void EmitFunctionBodyEnd() override;

	void EmitInstruction(const MachineInstr *MI);
};
}

#endif /* LIB_TARGET_I0_I0ASMPRINTER_H_ */
