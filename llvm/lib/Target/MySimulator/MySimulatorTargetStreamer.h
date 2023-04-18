#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETSTREAMER_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETSTREAMER_H__

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class MySimulatorTargetStreamer : public MCTargetStreamer {
public:
  MySimulatorTargetStreamer(MCStreamer &S);
  ~MySimulatorTargetStreamer() override;
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_TARGETSTREAMER_H__
