#include "MySimulatorInfo.h"

#define GET_REGINFO_ENUM
#include "MySimulatorGenRegisterInfo.inc"

namespace llvm {
namespace MySimulatorABI {
MCRegister getBPReg() { return MySimulator::X9; }
MCRegister getSCSPReg() { return MySimulator::X18; }
} // namespace MySimulatorABI
} // namespace llvm
