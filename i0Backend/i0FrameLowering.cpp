#include "i0FrameLowering.h"
#include "i0InstrInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"

namespace llvm {

i0FrameLowering::i0FrameLowering(const i0Subtarget& sti) :
		TargetFrameLowering(StackGrowsDown, 8, 0, 8), STI(sti) {
}

bool i0FrameLowering::hasFP(const MachineFunction& MF) const {
	auto* MFI = MF.getFrameInfo();
	return MF.getTarget().Options.DisableFramePointerElim(MF)
			|| MFI->hasVarSizedObjects() || MFI->isFrameAddressTaken();
}

const i0FrameLowering* i0FrameLowering::create(const i0Subtarget& ST) {
	return new i0FrameLowering(ST);
}

void i0FrameLowering::emitPrologue(MachineFunction &MF) const {

	MachineBasicBlock& MBB = MF.front();
	MachineFrameInfo* MFI = MF.getFrameInfo();
	MachineBasicBlock::iterator I = MBB.begin();
	const i0InstrInfo& TII =
			*static_cast<const i0InstrInfo*>(MF.getSubtarget().getInstrInfo());

	DebugLoc DL;
	if (I != MBB.end()) {
		DL = I->getDebugLoc();
	}

	uint64_t stackSize = MFI->getStackSize();
	BuildMI(MBB, I, DL, TII.get(i0::ADDrir)).addReg(i0::SPq).addReg(i0::SPq).addImm(
			-stackSize);
	BuildMI(MBB, I, DL, TII.get(i0::MOVrr)).addReg(i0::BPq).addReg(i0::SPq);

}
void i0FrameLowering::emitEpilogue(MachineFunction &MF,
		MachineBasicBlock &MBB) const {

	MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();
	const i0InstrInfo& TII =
			*static_cast<const i0InstrInfo*>(MF.getSubtarget().getInstrInfo());
	DebugLoc DL = MBBI->getDebugLoc();
	BuildMI(MBB, MBBI, DL, TII.get(i0::MOVrr)).addReg(i0::SPq).addReg(i0::BPq);
}
}
