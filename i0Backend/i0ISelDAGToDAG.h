#ifndef LIB_TARGET_I0_I0ISELDAGTODAG_H_
#define LIB_TARGET_I0_I0ISELDAGTODAG_H_

#include "i0TargetMachine.h"
#include "i0InstrInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {
class i0DAGToDAGISel: public SelectionDAGISel {

	i0TargetMachine& TM;
public:
	explicit i0DAGToDAGISel(i0TargetMachine& tm);
	SDNode* Select(SDNode*) override;
	bool SelectAddr(SDNode *Parent, SDValue Addr, SDValue &Base,
			SDValue &Offset);
	bool SelectAddrAbs(SDNode *Parent, SDValue Addr, SDValue &Abs);
private:
#include "i0GenDAGISel.inc"
	const char* getPassName() const override;
	//bool runOnMachineFunction(MachineFunction& MF) override;
	/*bool SelectInlineAsmMemoryOperand(const SDValue &Op, char ConstraintCode,
            std::vector<SDValue> &OutOps) ;*/
};

FunctionPass* createi0ISelDag(i0TargetMachine& TM);

}

#endif /* LIB_TARGET_I0_I0ISELDAGTODAG_H_ */
