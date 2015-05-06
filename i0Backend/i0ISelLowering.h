#ifndef LIB_TARGET_I0_I0ISELLOWERING_H_
#define LIB_TARGET_I0_I0ISELLOWERING_H_

#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/IR/Function.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {

namespace i0ISD{
enum NodeType{
	FIRST_NUMBER = ISD::BUILTIN_OP_END,
	JmpLink,
	Ret
};
}

class i0Subtarget;
class i0TargetMachine;

class i0TargetLowering: public TargetLowering {
	const i0Subtarget& Subtarget;

public:
	static const i0TargetLowering* create(
		i0TargetMachine& TM, const i0Subtarget& STI);
	i0TargetLowering(i0TargetMachine& TM, const i0Subtarget& STI);
	SDValue LowerGlobalAddr(SDValue Op, SelectionDAG &DAG) const;
	SDValue LowerSELECT(SDValue Op, SelectionDAG &DAG) const;
	//SDValue LowerBlockAddr(SDValue Op, SelectionDAG& DAG) const;
	SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const;
	SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
			bool IsVarArg, const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl,
			SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const override;

	SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
			SmallVectorImpl<SDValue> &InVals) const override;

	bool CanLowerReturn(CallingConv::ID CallConv, MachineFunction &MF,
			bool isVarArg, const SmallVectorImpl<ISD::OutputArg> &Outs,
			LLVMContext &Context) const override;

	SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
			const SmallVectorImpl<ISD::OutputArg> &Outs,
			const SmallVectorImpl<SDValue> &OutVals, SDLoc dl,
			SelectionDAG &DAG) const override;
	const char* getTargetNodeName(unsigned Opcode) const;
};
}

#endif /* LIB_TARGET_I0_I0ISELLOWERING_H_ */
