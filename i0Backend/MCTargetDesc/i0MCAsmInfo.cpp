#include "i0MCAsmInfo.h"
#include <cstdio>

namespace llvm{

i0AsmInfo::i0AsmInfo(StringRef TT){

	fprintf(stderr, "initializing i0AsmInfo by Triple: %s\n",
			TT.str().c_str());
}

}
