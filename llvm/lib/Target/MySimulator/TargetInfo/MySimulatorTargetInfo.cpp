#include "MySimulator.h"
#include "llvm/IR/Module.h"
#include "TargetInfo/MySimulatorTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheMySimulatorTarget() {
  static Target TheMySimulatorTarget;
  return TheMySimulatorTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMySimulatorTargetInfo() {
  RegisterTarget<Triple::MySimulator, false> X(getTheMySimulatorTarget(), "MySimulator", "MySimulator (32-bit arch) - for LLVM course in MIPT", "MySimulator");
}
