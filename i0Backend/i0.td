include "llvm/Target/Target.td"

include "i0RegisterInfo.td"
include "i0CallingConv.td"
include "i0InstrFormats.td"
include "i0InstrInfo.td"

def i0InstrInfo : InstrInfo;

def i0subtarget : Processor<"i0currimpl", NoItineraries, []>;

def i0 : Target{

let InstructionSet = i0InstrInfo;

}
