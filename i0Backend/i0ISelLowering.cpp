#include "i0ISelLowering.h"
#include "i0TargetMachine.h"
#include "i0RegisterInfo.h"
#include "llvm/Target/TargetLowering.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE i0

namespace llvm {

const char* i0TargetLowering::getTargetNodeName(unsigned Opcode) const{
	switch(Opcode){
	case i0ISD::JmpLink:
		return "i0ISD::JmpLink";
	case i0ISD::Ret:
		return "i0ISD::Ret";
	default:
		llvm_unreachable("unknown Opcode");
	}
}

i0TargetLowering::i0TargetLowering(i0TargetMachine& TM, const i0Subtarget& STI) :
		TargetLowering(TM), Subtarget(STI) {

	addRegisterClass(MVT::i64, &i0::GR64RegClass);
	setBooleanContents(ZeroOrOneBooleanContent);
	setBooleanVectorContents(ZeroOrNegativeOneBooleanContent);

	setOperationAction(ISD::BR_CC, MVT::i64, Expand);
	setOperationAction(ISD::SELECT_CC, MVT::i64, Expand);
	//expand the select_cc
	setOperationAction(ISD::GlobalAddress, MVT::i64, Custom);

	setStackPointerRegisterToSaveRestore(i0::SPq);
	computeRegisterProperties();

}

const i0TargetLowering* i0TargetLowering::create(i0TargetMachine& TM,
		const i0Subtarget& STI) {
	return new i0TargetLowering(TM, STI);
}

SDValue i0TargetLowering::LowerGlobalAddr(SDValue Op, SelectionDAG &DAG) const {
	GlobalAddressSDNode* N = cast<GlobalAddressSDNode>(Op);
	EVT Ty = Op.getValueType();
	const GlobalValue* GV = N->getGlobal();
	SDLoc DL(N);
	return DAG.getTargetGlobalAddress(GV, DL, Ty, 0);
}

SDValue i0TargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {

	dbgs() << "try to lower" << Op.getOpcode();
	switch (Op.getOpcode()) {
	case ISD::GlobalAddress:
		return LowerGlobalAddr(Op, DAG);
		break;
	default:
		dbgs() << " can not lower\n";
	}
	return SDValue();
}

SDValue i0TargetLowering::LowerFormalArguments(SDValue Chain,
		CallingConv::ID CallConv, bool IsVarArg,
		const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc DL, SelectionDAG &DAG,
		SmallVectorImpl<SDValue> &InVals) const {

	if (CallConv != CallingConv::C) {
		dbgs() << "can not handle non-C callconv";
		exit(-1);
	}

	//std::vector<SDValue> Outchains;
	//Chain = DAG.getNode(ISD::TokenFactor, DL, MVT::Other, Outchains);

	return Chain;
}

SDValue i0TargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
		SmallVectorImpl<SDValue> &InVals) const {

	dbgs() << "not implemented";
	exit(-1);
}

SDValue i0TargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
		bool IsVarArg, const SmallVectorImpl<ISD::OutputArg> &Outs,
		const SmallVectorImpl<SDValue> &OutVals, SDLoc DL,
		SelectionDAG &DAG) const {

	SmallVector<SDValue, 4> RetOps(1, Chain);
	return DAG.getNode(i0ISD::Ret, DL, MVT::Other, RetOps);
}

bool i0TargetLowering::CanLowerReturn(CallingConv::ID CallConv,
		MachineFunction &MF, bool isVarArg,
		const SmallVectorImpl<ISD::OutputArg> &Outs,
		LLVMContext &Context) const {
	return true;
}

}
