#ifndef LIB_TARGET_I0_I0FRAMELOWERING_H_
#define LIB_TARGET_I0_I0FRAMELOWERING_H_

#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {

class i0Subtarget;

class i0FrameLowering: public TargetFrameLowering {
	const i0Subtarget& STI;
public:
	i0FrameLowering(const i0Subtarget&);

	bool hasFP(const MachineFunction& MF) const override;
	virtual void emitPrologue(MachineFunction &MF) const override;
	virtual void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const
			override;
	static const i0FrameLowering* create(const i0Subtarget&);
};
}

#endif /* LIB_TARGET_I0_I0FRAMELOWERING_H_ */
