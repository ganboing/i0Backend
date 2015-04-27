#include "i0AsmBackend.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {

i0AsmBackend::i0AsmBackend() :
		MCAsmBackend() {
}

MCObjectWriter* i0AsmBackend::createObjectWriter(raw_ostream &OS) const {
	llvm_unreachable("i0AsmBackend::createObjectWriter");
}
void i0AsmBackend::applyFixup(const MCFixup &Fixup, char *Data,
		unsigned DataSize, uint64_t Value, bool IsPCRel) const {

	llvm_unreachable("i0AsmBackend::applyFixup");
}
unsigned i0AsmBackend::getNumFixupKinds() const {

	llvm_unreachable("i0AsmBackend::getNumFixupKinds");
}

bool i0AsmBackend::mayNeedRelaxation(const MCInst &Inst) const {
	return false;
}

bool i0AsmBackend::fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
		const MCRelaxableFragment *DF, const MCAsmLayout &Layout) const {
	llvm_unreachable("i0AsmBackend::fixupNeedsRelaxation");
}
bool i0AsmBackend::writeNopData(uint64_t Count, MCObjectWriter *OW) const {
	return true;
}
void i0AsmBackend::relaxInstruction(const MCInst &Inst, MCInst &Res) const {
}

}
