#include "i0SelectionDAGInfo.h"

namespace llvm{

i0SelectionDAGInfo::i0SelectionDAGInfo(const DataLayout& DL):
		TargetSelectionDAGInfo(&DL)
{}

i0SelectionDAGInfo::~i0SelectionDAGInfo()
{}

}
