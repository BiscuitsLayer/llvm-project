#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCASMINFO_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCASMINFO_H__

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class MySimulatorMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit MySimulatorMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCASMINFO_H__
