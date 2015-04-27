#ifndef LIB_TARGET_I0_I0INSTRINFO_H_
#define LIB_TARGET_I0_I0INSTRINFO_H_

#include "llvm/Target/TargetInstrInfo.h"
#include "i0RegisterInfo.h"

#define GET_INSTRINFO_HEADER
#define GET_INSTRINFO_ENUM
#include "i0GenInstrInfo.inc"

namespace llvm {

class i0Subtarget;
class i0RegisterInfo;

class i0InstrInfo: public i0GenInstrInfo {
	const i0Subtarget& Subtarget;
	const i0RegisterInfo RI;
public:
	static const i0InstrInfo* create(i0Subtarget& STI);
	const i0RegisterInfo& getRegisterInfo() const;
	explicit i0InstrInfo(const i0Subtarget& STI);
	/*void adjustStackPtr(i0FunctionInfo *i0FI, int64_t Amount,
			MachineBasicBlock& MBB, MachineBasicBlock::iterator I) const;*/
	void storeRegToStackSlot(MachineBasicBlock &MBB,
			MachineBasicBlock::iterator MBBI, unsigned SrcReg, bool isKill,
			int FrameIndex, const TargetRegisterClass *RC,
			const TargetRegisterInfo *TRI) const override;
	void loadRegFromStackSlot(MachineBasicBlock &MBB,
			MachineBasicBlock::iterator MBBI, unsigned DestReg, int FrameIndex,
			const TargetRegisterClass *RC, const TargetRegisterInfo *TRI) const
					override;
	void copyPhysReg(MachineBasicBlock &MBB,
	                   MachineBasicBlock::iterator MI, DebugLoc DL,
	                   unsigned DestReg, unsigned SrcReg,
	                   bool KillSrc) const override;
};

}
#endif /* LIB_TARGET_I0_I0INSTRINFO_H_ */
