#ifndef LIB_TARGET_I0_I0REGISTERINFO_H_
#define LIB_TARGET_I0_I0REGISTERINFO_H_

#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#define GET_REGINFO_ENUM
#include "i0GenRegisterInfo.inc"

namespace llvm {

class i0Subtarget;

class i0RegisterInfo: public i0GenRegisterInfo {
public:
	const i0Subtarget& Subtarget;

	i0RegisterInfo(const i0Subtarget& ST);
	/// getRegisterNumbering - Given the enum value for some register, e.g.
	static unsigned getRegisterNumbering(unsigned RegEnum);

	/// Code Generation virtual methods...
	const uint16_t *getCalleeSavedRegs(const MachineFunction* MF = 0) const;
	const uint32_t *getCallPreservedMask(CallingConv::ID) const;

	BitVector getReservedRegs(const MachineFunction &MF) const;

	/// Stack Frame Processing Methods
	void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
			unsigned FIOperandNum, RegScavenger *RS = nullptr) const override;

	/// Debug information queries.
	unsigned getFrameRegister(const MachineFunction &MF) const;
};
}

#endif /* LIB_TARGET_I0_I0REGISTERINFO_H_ */
