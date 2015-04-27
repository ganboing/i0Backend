#ifndef LIB_TARGET_I0_MCTARGETDESC_I0ASMBACKEND_H_
#define LIB_TARGET_I0_MCTARGETDESC_I0ASMBACKEND_H_

#include "llvm/MC/MCAsmBackend.h"

namespace llvm {

class i0AsmBackend: public MCAsmBackend {
public:
	i0AsmBackend();
	MCObjectWriter *createObjectWriter(raw_ostream &OS) const override;
	void applyFixup(const MCFixup &Fixup, char *Data, unsigned DataSize,
			uint64_t Value, bool IsPCRel) const override;
	unsigned getNumFixupKinds() const override;
	void relaxInstruction(const MCInst &Inst, MCInst &Res) const override;
	bool writeNopData(uint64_t Count, MCObjectWriter *OW) const override;
	bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
			const MCRelaxableFragment *DF, const MCAsmLayout &Layout) const
					override;
	bool mayNeedRelaxation(const MCInst &Inst) const override;
};

}

#endif /* LIB_TARGET_I0_MCTARGETDESC_I0ASMBACKEND_H_ */
