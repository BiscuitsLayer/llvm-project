#ifndef __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_H__
#define __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_H__

#include "MCTargetDesc/MySimulatorMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class MySimulatorTargetMachine;
class FunctionPass;
class MySimulatorSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerMySimulatorMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                    AsmPrinter &AP);
bool LowerMySimulatorMachineOperandToMCOperand(const MachineOperand &MO,
                                         MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createMySimulatorISelDag(MySimulatorTargetMachine &TM,
                                CodeGenOpt::Level OptLevel);


// namespace MySimulator {
// enum {
// };
// } // namespace MySimulator

} // namespace llvm

#endif // __LLVM_LIB_TARGET_MY_SIMULATOR_MY_SIMULATOR_H__
