#ifndef LIB_TARGET_I0_MCTARGETDESC_I0MCTARGETDESC_H_
#define LIB_TARGET_I0_MCTARGETDESC_I0MCTARGETDESC_H_

#include "llvm/Support/TargetRegistry.h"

namespace llvm{

extern Target Thei0Target;

}

#define GET_REGINFO_ENUM
#include "i0GenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "i0GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "i0GenSubtargetInfo.inc"

#endif /* LIB_TARGET_I0_MCTARGETDESC_I0MCTARGETDESC_H_ */
