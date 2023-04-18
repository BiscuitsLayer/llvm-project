add_llvm_component_library(LLVMMySimulatorDesc
  MySimulatorInstPrinter.cpp
  MySimulatorMCAsmInfo.cpp
  MySimulatorMCTargetDesc.cpp
  MySimulatorInfo.cpp

  LINK_COMPONENTS
  MC
  MySimulatorInfo
  Support

  ADD_TO_COMPONENT
  MySimulator
  )
