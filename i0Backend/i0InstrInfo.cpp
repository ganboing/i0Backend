#include "i0InstrInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/MC/MCInstrInfo.h"

#include "i0Subtarget.h"
#include "llvm/Support/Debug.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "i0GenInstrInfo.inc"

namespace llvm {

const i0InstrInfo* i0InstrInfo::create(i0Subtarget& STI) {
	return new i0InstrInfo(STI);
}

i0InstrInfo::i0InstrInfo(const i0Subtarget& STI) :
		i0GenInstrInfo(i0::ADJCALLSTACKDOWN, i0::ADJCALLSTACKUP), Subtarget(
				STI), RI(STI) {

}

const i0RegisterInfo& i0InstrInfo::getRegisterInfo() const {
	return RI;
}

/*void i0InstrInfo::adjustStackPtr(i0FunctionInfo *i0FI, int64_t Amount,
 MachineBasicBlock& MBB, MachineBasicBlock::iterator I) const {

 DebugLoc DL = I != MBB.end() ? I->getDebugLoc() : DebugLoc();
 //BuildMI(MBB, I, DL, get())

 }*/

void i0InstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
		MachineBasicBlock::iterator I, unsigned SrcReg, bool isKill, int FI,
		const TargetRegisterClass *RC, const TargetRegisterInfo *TRI) const {

	dbgs() << "storeRegToStack " << SrcReg << " to FI " << FI << "\n";
	MachineFunction& MF = *MBB.getParent();
	MachineFrameInfo& MFI = *MF.getFrameInfo();
	unsigned Align = MFI.getObjectAlignment(FI);
	int64_t Size = MFI.getObjectSize(FI);
	MachinePointerInfo MPI = MachinePointerInfo::getFixedStack(FI);
	MachineMemOperand* MMO = MF.getMachineMemOperand(MPI,
			MachineMemOperand::MOStore, Size, Align);

	DebugLoc DL;
	if (I != MBB.end())
		DL = I->getDebugLoc();
	BuildMI(MBB, I, DL, get(i0::Storer_64)).addReg(SrcReg,
			getKillRegState(isKill)).addFrameIndex(FI).addImm(0).addMemOperand(
			MMO);

}
void i0InstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
		MachineBasicBlock::iterator I, unsigned DestReg, int FI,
		const TargetRegisterClass *RC, const TargetRegisterInfo *TRI) const {

	dbgs() << "loadRegFromStack " << DestReg << " from FI " << FI << "\n";
	MachineFunction& MF = *MBB.getParent();
	MachineFrameInfo& MFI = *MF.getFrameInfo();
	unsigned Align = MFI.getObjectAlignment(FI);
	int64_t Size = MFI.getObjectSize(FI);
	MachinePointerInfo MPI = MachinePointerInfo::getFixedStack(FI);
	MachineMemOperand* MMO = MF.getMachineMemOperand(MPI,
			MachineMemOperand::MOLoad, Size, Align);
	DebugLoc DL;
	if (I != MBB.end())
		DL = I->getDebugLoc();
	BuildMI(MBB, I, DL, get(i0::Loadr_64), DestReg).addFrameIndex(FI).addImm(
			0).addMemOperand(MMO);

}
void i0InstrInfo::copyPhysReg(MachineBasicBlock &MBB,
		MachineBasicBlock::iterator MI, DebugLoc DL, unsigned DestReg,
		unsigned SrcReg, bool KillSrc) const {
	fprintf(stderr, "copyPhysReg from %d to %d\n", SrcReg, DestReg);

	MachineInstrBuilder MIB = BuildMI(MBB, MI, DL, get(i0::MOVrr));
	if (DestReg) {
		MIB.addReg(DestReg, RegState::Define);
	}
	if (SrcReg) {
		MIB.addReg(SrcReg, getKillRegState(KillSrc));
	}

}
}
