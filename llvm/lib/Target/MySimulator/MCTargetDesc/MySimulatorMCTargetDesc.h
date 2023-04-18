#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheMySimulatorTarget;

} // End llvm namespace

// Defines symbolic names for MySimulator registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MySimulatorGenRegisterInfo.inc"

// Defines symbolic names for the MySimulator instructions.
#define GET_INSTRINFO_ENUM
#include "MySimulatorGenInstrInfo.inc"

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__
