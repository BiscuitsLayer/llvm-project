#include "MySimulatorMCTargetDesc.h"
#include "TargetInfo/MySimulatorTargetInfo.h"
#include "MySimulatorInfo.h"
#include "MySimulatorInstPrinter.h"
#include "MySimulatorELFStreamer.h"
#include "MySimulatorMCObjectFIleInfo.h"
#include "MySimulatorMCAsmInfo.h"
#include "MySimulatorTargetStreamer.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

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

static MCTargetStreamer *createMySimulatorTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new MySimulatorTargetStreamer(S);
}

static MCObjectFileInfo *
createMySimulatorMCObjectFileInfo(MCContext &Ctx, bool PIC,
                            bool LargeCodeModel = false) {
  MCObjectFileInfo *MOFI = new MySimulatorMCObjectFileInfo();
  MOFI->initMCObjectFileInfo(Ctx, PIC, LargeCodeModel);
  return MOFI;
}

static MCTargetStreamer *
createMySimulatorObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new MySimulatorTargetELFStreamer(S, STI);
  return nullptr;
}

class MySimulatorMCInstrAnalysis : public MCInstrAnalysis {
public:
  explicit MySimulatorMCInstrAnalysis(const MCInstrInfo *Info)
      : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    if (isConditionalBranch(Inst)) {
      int64_t Imm;
      if (Size == 2)
        Imm = Inst.getOperand(1).getImm();
      else
        Imm = Inst.getOperand(2).getImm();
      Target = Addr + Imm;
      return true;
    }

    if (Inst.getOpcode() == MySimulator::JAL) {
      Target = Addr + Inst.getOperand(1).getImm();
      return true;
    }

    return false;
  }
};

static MCInstrAnalysis *createMySimulatorInstrAnalysis(const MCInstrInfo *Info) {
  return new MySimulatorMCInstrAnalysis(Info);
}

static MCTargetStreamer *createMySimulatorNullTargetStreamer(MCStreamer &S) {
  return new MySimulatorTargetStreamer(S);
}

namespace {
MCStreamer *createMySimulatorELFStreamer(const Triple &T, MCContext &Context,
                                   std::unique_ptr<MCAsmBackend> &&MAB,
                                   std::unique_ptr<MCObjectWriter> &&MOW,
                                   std::unique_ptr<MCCodeEmitter> &&MCE,
                                   bool RelaxAll) {
  return createMySimulatorELFStreamer(Context, std::move(MAB), std::move(MOW),
                                std::move(MCE), RelaxAll);
}
} // end anonymous namespace

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMySimulatorTargetMC() {
  // Register the MC asm info.
  Target &TheMySimulatorTarget = getTheMySimulatorTarget();
  RegisterMCAsmInfoFn X(TheMySimulatorTarget, createMySimulatorMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCObjectFileInfo(TheMySimulatorTarget, createMySimulatorMCObjectFileInfo);
  TargetRegistry::RegisterMCInstrInfo(TheMySimulatorTarget, createMySimulatorMCInstrInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheMySimulatorTarget, createMySimulatorMCRegisterInfo);

  TargetRegistry::RegisterMCAsmBackend(TheMySimulatorTarget, createMySimulatorAsmBackend);
  TargetRegistry::RegisterMCCodeEmitter(TheMySimulatorTarget, createMySimulatorMCCodeEmitter);
  TargetRegistry::RegisterMCInstPrinter(TheMySimulatorTarget, createMySimulatorMCInstPrinter);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheMySimulatorTarget,
                                          createMySimulatorMCSubtargetInfo);
  TargetRegistry::RegisterELFStreamer(TheMySimulatorTarget, createMySimulatorELFStreamer);
  TargetRegistry::RegisterObjectTargetStreamer(
        TheMySimulatorTarget, createMySimulatorObjectTargetStreamer);
  TargetRegistry::RegisterMCInstrAnalysis(TheMySimulatorTarget, createMySimulatorInstrAnalysis);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheMySimulatorTarget, createMySimulatorMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheMySimulatorTarget,
                                            createMySimulatorTargetAsmStreamer);

  TargetRegistry::RegisterNullTargetStreamer(TheMySimulatorTarget,
                                               createMySimulatorNullTargetStreamer);                   
}
