#include "i0AsmPrinter.h"
#include "i0MachineFunction.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/MC/MCSymbol.h"

namespace llvm {

i0AsmPrinter::i0AsmPrinter(TargetMachine& TM, MCStreamer& Streamer) :
		AsmPrinter(TM, Streamer), i0FI(nullptr), MCcxt(nullptr) {
}

bool i0AsmPrinter::runOnMachineFunction(MachineFunction& MF) {
	dbgs() << "asm print run on " << MF.getName() << "\n";
	i0FI = MF.getInfo<i0FunctionInfo>();
	return AsmPrinter::runOnMachineFunction(MF);
}

void i0AsmPrinter::EmitFunctionEntryLabel() {
	OutStreamer.EmitRawText(".proc ");
	//OutStreamer.EmitRawText(CurrentFnSym->getName());
}

void i0AsmPrinter::EmitFunctionBodyStart() {
	MCcxt = &MF->getContext();
}

void i0AsmPrinter::EmitFunctionBodyEnd() {
	OutStreamer.EmitRawText(".endp ");
	OutStreamer.EmitRawText(CurrentFnSym->getName());
}

void i0AsmPrinter::EmitStartOfAsmFile(Module& M) {
	OutStreamer.EmitRawText("\t.i0_asm\n");
}

MCOperand i0AsmPrinter::lowerToMcop(const MachineOperand& MCOP) {
	MachineOperand::MachineOperandType MCOPTy = MCOP.getType();
	const MCSymbol* symbol = nullptr;
	switch (MCOPTy) {
	default:
		llvm_unreachable_internal("MCOPTy not handled");
		break;
	case MachineOperand::MO_Register:
		return MCOperand::CreateReg(MCOP.getReg());
	case MachineOperand::MO_Immediate:
		return MCOperand::CreateImm(MCOP.getImm());
	case MachineOperand::MO_MachineBasicBlock:
		symbol = MCOP.getMBB()->getSymbol();
		break;
	case MachineOperand::MO_BlockAddress:
		symbol = GetBlockAddressSymbol(MCOP.getBlockAddress());
		break;
	case MachineOperand::MO_GlobalAddress:
		symbol = getSymbol(MCOP.getGlobal());
		break;
	}
	const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::Create(symbol,
			MCSymbolRefExpr::VK_None, *MCcxt);
	return MCOperand::CreateExpr(MCSym);
}

MCInst i0AsmPrinter::lowerToMcinst(const MachineInstr& MCI) {
	MCInst inst;
	inst.setOpcode(MCI.getOpcode());
	for (unsigned i = 0, j = MCI.getNumOperands(); i != j; ++i) {
		const MachineOperand& MO = MCI.getOperand(i);
		inst.addOperand(lowerToMcop(MO));
	}
	return inst;
}

void i0AsmPrinter::EmitInstruction(const MachineInstr* MI) {
	MCInst mcInst;

	if (MI->isInsideBundle()) {
		llvm_unreachable("should not happen");
	}
	OutStreamer.EmitInstruction(lowerToMcinst(*MI), getSubtargetInfo());
}

extern Target Thei0Target;

extern "C" void LLVMInitializei0AsmPrinter() {

	RegisterAsmPrinter<i0AsmPrinter> X(Thei0Target);
}
}

