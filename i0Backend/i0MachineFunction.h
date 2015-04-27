#ifndef LIB_TARGET_I0_I0MACHINEFUNCTION_H_
#define LIB_TARGET_I0_I0MACHINEFUNCTION_H_

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm{

class i0FunctionInfo : public MachineFunctionInfo
{
	MachineFunction& MF;
public:
	i0FunctionInfo(MachineFunction& MF);
};

}

#endif /* LIB_TARGET_I0_I0MACHINEFUNCTION_H_ */
