#include "i0ISelDAGToDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "i0-isel"

namespace llvm {

i0DAGToDAGISel::i0DAGToDAGISel(i0TargetMachine& tm) :
		SelectionDAGISel(tm), TM(tm) {
}

bool i0DAGToDAGISel::SelectAddr(SDNode *Parent, SDValue Addr, SDValue &Base,
		SDValue &Offset) {
	EVT ValTy = Addr.getValueType();

	// if Address is FI, get the TargetFrameIndex.
	if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
		Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
		Offset = CurDAG->getTargetConstant(0, ValTy);
		return true;
	}

	// Addresses of the form FI+const or FI|const
	if (CurDAG->isBaseWithConstantOffset(Addr)) {
		ConstantSDNode *CN = dyn_cast<ConstantSDNode>(Addr.getOperand(1));
		if (isInt<32>(CN->getSExtValue())) {

			// If the first operand is a FI, get the TargetFI Node
			if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(
					Addr.getOperand(0)))
				Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
			else
				Base = Addr.getOperand(0);

			Offset = CurDAG->getTargetConstant(CN->getZExtValue(), ValTy);
			return true;
		}
	}

	return false;
	Base = Addr;
	Offset = CurDAG->getTargetConstant(0, ValTy);
}

bool i0DAGToDAGISel::SelectAddrAbs(SDNode *Parent, SDValue Addr, SDValue &Abs){
	return false;
}

/*bool  i0DAGToDAGISel::SelectInlineAsmMemoryOperand(const SDValue &Op, char ConstraintCode,
            std::vector<SDValue> &OutOps){
return SelectionDAGISel(Op, ConstraintCode, OutOps);
}*/

SDNode* i0DAGToDAGISel::Select(SDNode* Node) {
	unsigned Opcode = Node->getOpcode();

	// Dump information about the Node being selected
	DEBUG(errs() << "Selecting: "; Node->dump(CurDAG); errs() << "\n");

	// If we have a custom node, we already have selected!
	if (Node->isMachineOpcode()) {
		DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
		Node->setNodeId(-1);
		return nullptr;
	}

	switch(Opcode){
	case ISD::ADDE:
		break;
	case ISD::SUBE:
		break;
	}

	return SelectCode(Node);
}

const char* i0DAGToDAGISel::getPassName() const{
	return "i0 DAG->DAG";
}

FunctionPass* createi0ISelDag(i0TargetMachine &TM) {
	return new i0DAGToDAGISel(TM);
}
}
