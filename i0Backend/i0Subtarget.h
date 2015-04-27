#ifndef LIB_TARGET_I0_I0SUBTARGET_H_
#define LIB_TARGET_I0_I0SUBTARGET_H_

#include "i0SelectionDAGInfo.h"
#include "i0InstrInfo.h"
#include "i0RegisterInfo.h"
#include "i0ISelLowering.h"
#include "llvm/Target/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"

#define GET_SUBTARGETINFO_HEADER
#include "i0GenSubtargetInfo.inc"

namespace llvm {

class i0InstrInfo;
class i0TargetLowering;
class i0FrameLowering;
class i0TargetMachine;

class i0Subtarget : public i0GenSubtargetInfo{

	i0TargetMachine* const TM;
	DataLayout const DL;       // Calculates type size & alignment
	const i0InstrInfo* const InstrInfo;
	const i0TargetLowering* const TLInfo;
	i0SelectionDAGInfo const TSInfo;
	const i0FrameLowering* const FrameLowering;
public:
	//const InstrItineraryData *getInstrItineraryData() const override;
	const i0InstrInfo *getInstrInfo() const override;
	const TargetFrameLowering *getFrameLowering() const override ;
	const i0RegisterInfo *getRegisterInfo() const override;
	const i0TargetLowering *getTargetLowering() const override ;
	const i0SelectionDAGInfo *getSelectionDAGInfo() const override ;
	const DataLayout *getDataLayout() const override ;
	i0Subtarget(const std::string& TT, const std::string& CPU, const std::string& FS,
			i0TargetMachine* _TM);
	void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
};

}
#endif /* LIB_TARGET_I0_I0SUBTARGET_H_ */
