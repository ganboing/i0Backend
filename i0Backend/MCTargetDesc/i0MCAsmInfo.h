#ifndef LIB_TARGET_I0_MCTARGETDESC_I0MCASMINFO_H_
#define LIB_TARGET_I0_MCTARGETDESC_I0MCASMINFO_H_

#include "llvm/MC/MCAsmInfo.h"

namespace llvm{

class i0AsmInfo : public MCAsmInfo{
public:
	explicit i0AsmInfo(StringRef TT);
};

}


#endif /* LIB_TARGET_I0_MCTARGETDESC_I0MCASMINFO_H_ */
