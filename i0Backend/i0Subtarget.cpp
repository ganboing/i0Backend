#include "i0Subtarget.h"

#include "i0ISelLowering.h"
#include "i0InstrInfo.h"
#include "i0RegisterInfo.h"
#include "i0FrameLowering.h"

#define DEBUG_TYPE "i0-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "i0GenSubtargetInfo.inc"

namespace llvm {

const i0InstrInfo * i0Subtarget::getInstrInfo() const {
	return InstrInfo;
}
const TargetFrameLowering * i0Subtarget::getFrameLowering() const {
	return FrameLowering;
}
const i0RegisterInfo * i0Subtarget::getRegisterInfo() const {
	return &InstrInfo->getRegisterInfo();
}
const i0TargetLowering * i0Subtarget::getTargetLowering() const {
	return TLInfo;
}
const i0SelectionDAGInfo * i0Subtarget::getSelectionDAGInfo() const {
	return &TSInfo;
}
const DataLayout *i0Subtarget::getDataLayout() const {
	return &DL;
}
i0Subtarget::i0Subtarget(const std::string& TT, const std::string& CPU,
		const std::string& FS, i0TargetMachine* _TM) :
		TM(_TM), i0GenSubtargetInfo(TT, CPU, FS), DL(
				"e-p:64:64:64-i8:8:8-i32:32:32-i64:64:64-n64-S64"), TSInfo(DL), InstrInfo(
				i0InstrInfo::create(*this)), FrameLowering(
				i0FrameLowering::create(*this)), TLInfo(
				i0TargetLowering::create(*_TM, *this)) {
}
}
