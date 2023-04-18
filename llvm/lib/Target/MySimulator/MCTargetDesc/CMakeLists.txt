add_llvm_component_library(LLVMMySimulatorDesc
  MySimulatorInstPrinter.cpp
  MySimulatorMCAsmInfo.cpp
  MySimulatorMCTargetDesc.cpp
  MySimulatorInfo.cpp
  MySimulatorAsmBackend.cpp
  MySimulatorMCCodeEmitter.cpp
  MySimulatorMCExpr.cpp
  MySimulatorELFObjectWriter.cpp
  MySimulatorTargetStreamer.cpp
  MySimulatorELFStreamer.cpp
  MySimulatorMCObjectFIleInfo.cpp

  LINK_COMPONENTS
  MC
  MySimulatorInfo
  Support

  ADD_TO_COMPONENT
  MySimulator
  )
