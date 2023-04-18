#include "MySimulatorMCTargetDesc.h"
#include "TargetInfo/MySimulatorTargetInfo.h"
#include "MySimulatorInfo.h"
#include "MySimulatorInstPrinter.h"
#include "MySimulatorMCAsmInfo.h"
#include "MySimulatorTargetStreamer.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "MySimulatorGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "MySimulatorGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MySimulatorGenSubtargetInfo.inc"

static MCInstrInfo *createMySimulatorMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitMySimulatorMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createMySimulatorMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitMySimulatorMCRegisterInfo(X, MySimulator::X1);
  return X;
}

static MCSubtargetInfo *createMySimulatorMCSubtargetInfo(const Triple &TT,
                                                  StringRef CPU, StringRef FS) {
  return createMySimulatorMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createMySimulatorMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new MySimulatorMCAsmInfo(TT);
  MCRegister SP = MRI.getDwarfRegNum(MySimulator::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createMySimulatorMCInstPrinter(const Triple &T,
                                              unsigned SyntaxVariant,
                                              const MCAsmInfo &MAI,
                                              const MCInstrInfo &MII,
                                              const MCRegisterInfo &MRI) {
  return new MySimulatorInstPrinter(MAI, MII, MRI);
}

MySimulatorTargetStreamer::MySimulatorTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
MySimulatorTargetStreamer::~MySimulatorTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new MySimulatorTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMySimulatorTargetMC() {
  // Register the MC asm info.
  Target &TheMySimulatorTarget = getTheMySimulatorTarget();
  RegisterMCAsmInfoFn X(TheMySimulatorTarget, createMySimulatorMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheMySimulatorTarget, createMySimulatorMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheMySimulatorTarget, createMySimulatorMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheMySimulatorTarget,
                                          createMySimulatorMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheMySimulatorTarget, createMySimulatorMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheMySimulatorTarget,
                                            createTargetAsmStreamer);
}
