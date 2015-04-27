#ifndef LIB_TARGET_I0_I0SELECTIONDAGINFO_H_
#define LIB_TARGET_I0_I0SELECTIONDAGINFO_H_

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm{

class i0SelectionDAGInfo : public TargetSelectionDAGInfo{
public:
	explicit i0SelectionDAGInfo(const DataLayout& DL);
	~i0SelectionDAGInfo();
};
}

#endif /* LIB_TARGET_I0_I0SELECTIONDAGINFO_H_ */
