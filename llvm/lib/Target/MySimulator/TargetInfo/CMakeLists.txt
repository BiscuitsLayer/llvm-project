add_llvm_component_library(LLVMMySimulatorInfo
  MySimulatorTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  MySimulator
  )
