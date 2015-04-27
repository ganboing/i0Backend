#include "llvm/Support/TargetRegistry.h"

namespace llvm{

Target Thei0Target;

extern "C" void LLVMInitializei0TargetInfo(){
	RegisterTarget<Triple::i0, false>
	  X(Thei0Target, "i0", "i0");
}

}
