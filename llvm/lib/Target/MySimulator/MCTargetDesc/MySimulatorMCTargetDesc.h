#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__

#include "llvm/Support/DataTypes.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Config/config.h"

#include <memory>

namespace llvm {
class Triple;
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;


extern Target TheMySimulatorTarget;

MCCodeEmitter *createMySimulatorMCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

std::unique_ptr<MCObjectTargetWriter> createMySimulatorELFObjectWriter(uint8_t OSABI,
                                                                 bool Is64Bit);
                                                         
MCAsmBackend *createMySimulatorAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);
} // End llvm namespace

// Defines symbolic names for MySimulator registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MySimulatorGenRegisterInfo.inc"

// Defines symbolic names for the MySimulator instructions.
#define GET_INSTRINFO_ENUM
#include "MySimulatorGenInstrInfo.inc"

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MY_SIMULATOR_MCTARGETDESC_H__
