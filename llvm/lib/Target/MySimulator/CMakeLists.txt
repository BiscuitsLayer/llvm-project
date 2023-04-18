add_llvm_component_group(MySimulator)

set(LLVM_TARGET_DEFINITIONS MySimulator.td)

# Generate MySimulatorGenRegisterInfo.inc and MySimulatorGenInstrInfo.inc which included by
#  your hand code C++ files.
# MySimulatorGenRegisterInfo.inc came from MySimulatorRegisterInfo.td, MySimulatorGenInstrInfo.inc
#  came from MySimulatorInstrInfo.td.
tablegen(LLVM MySimulatorGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MySimulatorGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MySimulatorGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MySimulatorGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM MySimulatorGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MySimulatorGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM MySimulatorGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM MySimulatorGenDAGISel.inc -gen-dag-isel)

#tablegen(LLVM MySimulatorGenDisassemblerTables.inc -gen-disassembler)

# MySimulatorCommonTableGen must be defined
add_public_tablegen_target(MySimulatorCommonTableGen)

# MySimulatorCodeGen should match with LLVMBuild.txt MySimulatorCodeGen
add_llvm_target(MySimulatorCodeGen
  MySimulatorAsmPrinter.cpp
  MySimulatorFrameLowering.cpp
  MySimulatorInstrInfo.cpp
  MySimulatorISelDagToDag.cpp
  MySimulatorISelLowering.cpp
  MySimulatorMachineFunctionInfo.cpp
  MySimulatorMCInstLower.cpp
  MySimulatorRegisterInfo.cpp
  MySimulatorSubtarget.cpp
  MySimulatorTargetMachine.cpp
  MySimulatorMatInt.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  MySimulatorDesc
  MySimulatorInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  MySimulator
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
