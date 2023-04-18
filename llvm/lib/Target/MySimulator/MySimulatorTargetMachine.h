#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETMACHINE_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETMACHINE_H__

#include "MySimulatorInstrInfo.h"
#include "MySimulatorSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class MySimulatorTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  MySimulatorSubtarget Subtarget;
  // mutable StringMap<std::unique_ptr<MySimulatorSubtarget>> SubtargetMap;

public:
  MySimulatorTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT);
  ~MySimulatorTargetMachine() override;

  const MySimulatorSubtarget *getSubtargetImpl() const { return &Subtarget; }
  const MySimulatorSubtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

#if 0
  bool
  addPassesToEmitFile(PassManagerBase &, raw_pwrite_stream &,
                      raw_pwrite_stream *, CodeGenFileType,
                      bool /*DisableVerify*/ = true,
                      MachineModuleInfoWrapperPass *MMIWP = nullptr) override {
    return false;
  }
#endif
  // TargetTransformInfo getTargetTransformInfo(const Function &F) override;
};
} // end namespace llvm

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETMACHINE_H__
