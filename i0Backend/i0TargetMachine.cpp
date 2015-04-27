#include "i0TargetMachine.h"
#include "i0ISelDAGToDAG.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/TargetRegistry.h"

namespace llvm {

extern Target Thei0Target;

extern "C" void LLVMInitializei0Target() {
	// Register the target.
	RegisterTargetMachine<i0TargetMachine> X(Thei0Target);
}

i0TargetMachine::i0TargetMachine(const Target &T, StringRef TT, StringRef CPU,
		StringRef FS, TargetOptions Options, Reloc::Model RM,
		CodeModel::Model CM, CodeGenOpt::Level OL) :
		LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL), TLOF(
				new TargetLoweringObjectFileELF()), SubTarget(TT, CPU, FS, this) {
	initAsmInfo();
}

TargetLoweringObjectFile* i0TargetMachine::getObjFileLowering() const {
	return TLOF;
}


const i0Subtarget* i0TargetMachine::getSubtargetImpl() const {
	return &SubTarget;
}

TargetPassConfig* i0TargetMachine::createPassConfig(PassManagerBase& PM) {
	return new i0PassConfig(this, PM);
}

i0PassConfig::i0PassConfig(i0TargetMachine* TM, PassManagerBase& PM) :
		TargetPassConfig(TM, PM) {
}

bool i0PassConfig::addInstSelector() {
	addPass(createi0ISelDag(geti0TargetMachine()));
	return false;
}
}
