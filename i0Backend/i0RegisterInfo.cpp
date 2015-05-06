#include "i0RegisterInfo.h"
#include "i0FrameLowering.h"
#include "i0MachineFunction.h"
#include "i0Subtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "i0GenRegisterInfo.inc"

namespace llvm {

i0RegisterInfo::i0RegisterInfo(const i0Subtarget& ST) :
	i0GenRegisterInfo(i0::LRq),	Subtarget(ST) {
}

const uint16_t* i0RegisterInfo::getCalleeSavedRegs(
		const MachineFunction*MF) const {
	return i0_CSR_SaveList;
}

const uint32_t* i0RegisterInfo::getCallPreservedMask(CallingConv::ID) const {
	return i0_CSR_RegMask;
}

BitVector i0RegisterInfo::getReservedRegs(const MachineFunction& MF) const {

	BitVector Reserved(getNumRegs());
	Reserved.set(i0::SPq);
	Reserved.set(i0::LRq);
	//currently we reserve BP no matter the function use it or not
	//if (MF.getSubtarget().getFrameLowering()->hasFP(MF)) {
		Reserved.set(i0::BPq);
	//}
	return Reserved;
}

unsigned i0RegisterInfo::getFrameRegister(const MachineFunction& MF) const {
	const TargetFrameLowering* TFI = MF.getSubtarget().getFrameLowering();
	//const i0FrameLowering* i0TFI = dyn_cast<i0FrameLowering>(TFI);
	//assert(i0TFI != nullptr);
	return TFI->hasFP(MF) ? (i0::BPq) : (i0::SPq);
}

void i0RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
		int SPAdj, unsigned FIOperandNum, RegScavenger* RS) const {

	MachineInstr &MI = *II;
	MachineFunction & MF = *MI.getParent()->getParent();
	MachineFrameInfo* MFI = MF.getFrameInfo();
	i0FunctionInfo* i0FI = MF.getInfo<i0FunctionInfo>();

	dbgs() << "eliminateFI of " << MF.getFunction()->getName() << "\n";

	unsigned i;
	bool findFIOp = false;
	for (i = 0; i < MI.getNumOperands(); ++i) {
		if (MI.getOperand(i).isFI()) {
			findFIOp = true;
			break;
		}
	}

	int FrameIndex = MI.getOperand(i).getIndex();
	uint64_t stackSize = MF.getFrameInfo()->getStackSize();
	int64_t spOffset = MF.getFrameInfo()->getObjectOffset(FrameIndex);

	dbgs() << "FrameIndex = " << FrameIndex << "\nspOffset = " << spOffset
			<< "\nstackSize = " << stackSize << "\n";

	int64_t Offset = spOffset + stackSize;
	Offset += MI.getOperand(i + 1).getImm();

	dbgs() << "final offset = " << Offset << "\n";
	MI.getOperand(i).ChangeToRegister(i0::SPq, false);
	MI.getOperand(i + 1).ChangeToImmediate(Offset);
}

}
