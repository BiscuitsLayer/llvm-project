//===----------------------------------------------------------------------===//
// This is the top level entry point for the MySimulator target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// MySimulator Subtarget features
//===----------------------------------------------------------------------===//

//def FeatureDummy
//    : SubtargetFeature<"dummy", "Dummy", "true",
//                       "Dummy feature">;

defvar MySimulator32 = DefaultMode;

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "MySimulatorRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "MySimulatorSchedule.td"
include "MySimulatorCallingConv.td"

include "MySimulatorInstrInfo.td"
def MySimulatorInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// MySimulator processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-32", NoSchedModel, []>;

def MySimulatorAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;
  let AllowDuplicateRegisterNames = 1;
}


// Will generate MySimulatorGenAsmWrite.inc included by MySimulatorInstPrinter.cpp, contents
//  as follows,
// void MySimulatorInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *MySimulatorInstPrinter::getRegisterName(unsigned RegNo) {...}
def MySimulator : Target {
  let InstructionSet = MySimulatorInstrInfo;
}
