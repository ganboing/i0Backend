set(LLVM_TARGET_DEFINITIONS i0.td)

tablegen(LLVM i0GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM i0GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM i0GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM i0GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM i0GenAsmWriter.inc -gen-asm-writer)
#tablegen(LLVM i0GenCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(i0CommonTableGen)

add_llvm_target(i0CodeGen
dummy.cpp
i0InstrInfo.cpp
i0TargetMachine.cpp
i0RegisterInfo.cpp
i0ISelDAGToDAG.cpp
i0ISelLowering.cpp
i0FrameLowering.cpp
i0MachineFunction.cpp
i0Subtarget.cpp
i0SelectionDAGInfo.cpp
i0AsmPrinter.cpp
#i0MCInstrLower.cpp
)
add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

