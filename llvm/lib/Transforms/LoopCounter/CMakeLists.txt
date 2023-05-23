add_llvm_component_library(LLVMLoopCounter
  LoopCounter.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
