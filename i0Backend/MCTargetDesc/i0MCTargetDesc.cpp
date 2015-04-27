#include "i0MCTargetDesc.h"
#include "i0AsmBackend.h"
#include "i0MCAsmInfo.h"
#include "InstPrinter/i0InstPrinter.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"

#define GET_INSTRINFO_MC_DESC
#include "i0GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "i0GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "i0GenRegisterInfo.inc"

namespace llvm {

MCInstrInfo* createi0MCInstrInfo() {
	MCInstrInfo* X = new MCInstrInfo();
	Initi0MCInstrInfo(X);
	return X;
}

MCRegisterInfo* createi0MCRegisterInfo(StringRef TT) {
	fprintf(stderr, "initializing i0MCRegisterInfo with TT = %s\n",
			TT.str().c_str());
	MCRegisterInfo* X = new MCRegisterInfo();
	Initi0MCRegisterInfo(X, i0::LRq);
	return X;
}

MCSubtargetInfo* createi0MCSubtargetInfo(StringRef TT, StringRef CPU,
		StringRef FS) {
	fprintf(stderr, "initializing i0MCSubtargetInfo with "
			"TT = %s, CPU = %s, FS = %s", TT.str().c_str(), CPU.str().c_str(),
			FS.str().c_str());
	MCSubtargetInfo* X = new MCSubtargetInfo();
	Initi0MCSubtargetInfo(X, TT, CPU, FS);
	return X;
}

MCAsmInfo* createi0MCAsmInfo(const MCRegisterInfo& MRI, StringRef TT) {
	fprintf(stderr, "initializing i0MCAsmInfo with TT =  %s\n",
			TT.str().c_str());
	return new i0AsmInfo(TT);
}

MCCodeGenInfo* createi0MCCodeGenInfo(StringRef TT, Reloc::Model RM,
		CodeModel::Model CM, CodeGenOpt::Level OL) {

	fprintf(stderr, "initializing i0MCCodeGenInfo with TT = %s\n",
			TT.str().c_str());
	MCCodeGenInfo* X = new MCCodeGenInfo();
	X->InitMCCodeGenInfo(RM, CM, OL);
	return X;
}

MCInstPrinter* createi0MCInstPrinter(const Target &T, unsigned SyntaxVariant,
		const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI,
		const MCSubtargetInfo &STI) {
	return new i0InstPrinter(MAI, MII, MRI);
}

MCStreamer* createi0MCAsmStreamer(MCContext &Ctx, formatted_raw_ostream &OS,
		bool isVerboseAsm, bool useDwarfDirectory, MCInstPrinter *InstPrint,
		MCCodeEmitter *CE, MCAsmBackend *TAB, bool ShowInst) {
	return llvm::createAsmStreamer(Ctx, OS, isVerboseAsm, useDwarfDirectory,
			InstPrint, CE, TAB, ShowInst);
}

MCAsmBackend* createi0AsmBackend(const Target &T, const MCRegisterInfo &MRI,
		StringRef TT, StringRef CPU) {
return new i0AsmBackend();
}

extern "C" void LLVMInitializei0TargetMC() {

	fprintf(stderr, "initializing i0\n");
	RegisterMCAsmInfoFn X(Thei0Target, createi0MCAsmInfo);
	TargetRegistry::RegisterMCCodeGenInfo(Thei0Target, createi0MCCodeGenInfo);
	TargetRegistry::RegisterMCInstrInfo(Thei0Target, createi0MCInstrInfo);
	TargetRegistry::RegisterMCRegInfo(Thei0Target, createi0MCRegisterInfo);
	TargetRegistry::RegisterMCAsmBackend(Thei0Target, createi0AsmBackend);
	TargetRegistry::RegisterAsmStreamer(Thei0Target, createi0MCAsmStreamer);
	TargetRegistry::RegisterMCSubtargetInfo(Thei0Target,
			createi0MCSubtargetInfo);
	TargetRegistry::RegisterMCInstPrinter(Thei0Target, createi0MCInstPrinter);

}

}
