//===----------------------------------------------------------------------===//
//
// Implements the info about MySimulator target spec.
//
//===----------------------------------------------------------------------===//

#include "MySimulatorTargetMachine.h"
#include "MySimulator.h"
//#include "MySimulatorTargetTransformInfo.h"
#include "TargetInfo/MySimulatorTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetOptions.h"

#define DEBUG_TYPE "MySimulator"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// MySimulatorTargetMachine ctor - Create an ILP32 Architecture model
MySimulatorTargetMachine::MySimulatorTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

MySimulatorTargetMachine::~MySimulatorTargetMachine() = default;

namespace {

/// MySimulator Code Generator Pass Configuration Options.
class MySimulatorPassConfig : public TargetPassConfig {
public:
  MySimulatorPassConfig(MySimulatorTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  MySimulatorTargetMachine &getMySimulatorTargetMachine() const {
    return getTM<MySimulatorTargetMachine>();
  }

  bool addInstSelector() override;
  // void addPreEmitPass() override;
  // void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *MySimulatorTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MySimulatorPassConfig(*this, PM);
}

bool MySimulatorPassConfig::addInstSelector() {
  addPass(createMySimulatorISelDag(getMySimulatorTargetMachine(), getOptLevel()));
  return false;
}

// void MySimulatorPassConfig::addPreEmitPass() { llvm_unreachable(""); }

// void MySimulatorPassConfig::addPreRegAlloc() { llvm_unreachable(""); }

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMySimulatorTarget() {
  RegisterTargetMachine<MySimulatorTargetMachine> X(getTheMySimulatorTarget());
}

#if 0
TargetTransformInfo
MySimulatorTargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(MySimulatorTTIImpl(this, F));
}
#endif