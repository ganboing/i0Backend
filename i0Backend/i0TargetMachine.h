#ifndef LIB_TARGET_I0_I0TARGETMACHINE_H_
#define LIB_TARGET_I0_I0TARGETMACHINE_H_

#include "i0Subtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/Passes.h"

namespace llvm{

class i0TargetMachine: public LLVMTargetMachine {

	TargetLoweringObjectFileELF* TLOF;
	i0Subtarget SubTarget;

public:

	i0TargetMachine(const Target &T, StringRef TargetTriple, StringRef CPU,
			StringRef FS, TargetOptions Options, Reloc::Model RM,
			CodeModel::Model CM, CodeGenOpt::Level OL);
	virtual TargetPassConfig* createPassConfig(PassManagerBase& PM);

	const i0Subtarget* getSubtargetImpl() const override;

	TargetLoweringObjectFile* getObjFileLowering() const override;
private:

};

class i0PassConfig: public TargetPassConfig {
public:
	i0PassConfig(i0TargetMachine* TM, PassManagerBase& PM);
	//virtual bool addInstSelector() override;

	inline i0TargetMachine& geti0TargetMachine() const {
		return getTM<i0TargetMachine>();
	}
	inline const i0Subtarget& geti0SubTarget() const {
		return *geti0TargetMachine().getSubtargetImpl();
	}
	bool addInstSelector() override;
};
}

#endif /* LIB_TARGET_I0_I0TARGETMACHINE_H_ */
