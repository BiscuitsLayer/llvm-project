//===-- MySimulatorELFObjectWriter.cpp - MySimulator ELF Writer -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/MySimulatorFixupKinds.h"
#include "MCTargetDesc/MySimulatorMCExpr.h"
#include "MCTargetDesc/MySimulatorMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class MySimulatorELFObjectWriter : public MCELFObjectTargetWriter {
public:
  MySimulatorELFObjectWriter(uint8_t OSABI, bool Is64Bit);

  ~MySimulatorELFObjectWriter() override;

  // Return true if the given relocation must be with a symbol rather than
  // section plus offset.
  bool needsRelocateWithSymbol(const MCSymbol &Sym,
                               unsigned Type) const override {
    // TODO: this is very conservative, update once RISC-V psABI requirements
    //       are clarified.
    return true;
  }

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

MySimulatorELFObjectWriter::MySimulatorELFObjectWriter(uint8_t OSABI, bool Is64Bit)
    : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_MySimulator,
                              /*HasRelocationAddend*/ true) {}

MySimulatorELFObjectWriter::~MySimulatorELFObjectWriter() {}

unsigned MySimulatorELFObjectWriter::getRelocType(MCContext &Ctx,
                                            const MCValue &Target,
                                            const MCFixup &Fixup,
                                            bool IsPCRel) const {
  const MCExpr *Expr = Fixup.getValue();
  // Determine the type of the relocation
  unsigned Kind = Fixup.getTargetKind();
  if (Kind >= FirstLiteralRelocationKind)
    return Kind - FirstLiteralRelocationKind;
  if (IsPCRel) {
    switch (Kind) {
    default:
      Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
      return ELF::R_MY_SIMULATOR_NONE;
    case FK_Data_4:
    case FK_PCRel_4:
      return ELF::R_MY_SIMULATOR_32_PCREL;
    case MySimulator::fixup_MY_SIMULATOR_pcrel_hi20:
      return ELF::R_MY_SIMULATOR_PCREL_HI20;
    case MySimulator::fixup_MY_SIMULATOR_pcrel_lo12_i:
      return ELF::R_MY_SIMULATOR_PCREL_LO12_I;
    case MySimulator::fixup_MY_SIMULATOR_pcrel_lo12_s:
      return ELF::R_MY_SIMULATOR_PCREL_LO12_S;
    case MySimulator::fixup_MY_SIMULATOR_got_hi20:
      return ELF::R_MY_SIMULATOR_GOT_HI20;
    case MySimulator::fixup_MY_SIMULATOR_tls_got_hi20:
      return ELF::R_MY_SIMULATOR_TLS_GOT_HI20;
    case MySimulator::fixup_MY_SIMULATOR_tls_gd_hi20:
      return ELF::R_MY_SIMULATOR_TLS_GD_HI20;
    case MySimulator::fixup_MY_SIMULATOR_jal:
      return ELF::R_MY_SIMULATOR_JAL;
    case MySimulator::fixup_MY_SIMULATOR_branch:
      return ELF::R_MY_SIMULATOR_BRANCH;
    case MySimulator::fixup_MY_SIMULATOR_rvc_jump:
      return ELF::R_MY_SIMULATOR_RVC_JUMP;
    case MySimulator::fixup_MY_SIMULATOR_rvc_branch:
      return ELF::R_MY_SIMULATOR_RVC_BRANCH;
    case MySimulator::fixup_MY_SIMULATOR_call:
      return ELF::R_MY_SIMULATOR_CALL;
    case MySimulator::fixup_MY_SIMULATOR_call_plt:
      return ELF::R_MY_SIMULATOR_CALL_PLT;
    case MySimulator::fixup_MY_SIMULATOR_add_8:
      return ELF::R_MY_SIMULATOR_ADD8;
    case MySimulator::fixup_MY_SIMULATOR_sub_8:
      return ELF::R_MY_SIMULATOR_SUB8;
    case MySimulator::fixup_MY_SIMULATOR_add_16:
      return ELF::R_MY_SIMULATOR_ADD16;
    case MySimulator::fixup_MY_SIMULATOR_sub_16:
      return ELF::R_MY_SIMULATOR_SUB16;
    case MySimulator::fixup_MY_SIMULATOR_add_32:
      return ELF::R_MY_SIMULATOR_ADD32;
    case MySimulator::fixup_MY_SIMULATOR_sub_32:
      return ELF::R_MY_SIMULATOR_SUB32;
    case MySimulator::fixup_MY_SIMULATOR_add_64:
      return ELF::R_MY_SIMULATOR_ADD64;
    case MySimulator::fixup_MY_SIMULATOR_sub_64:
      return ELF::R_MY_SIMULATOR_SUB64;
    }
  }

  switch (Kind) {
  default:
    Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
    return ELF::R_MY_SIMULATOR_NONE;
  case FK_Data_1:
    Ctx.reportError(Fixup.getLoc(), "1-byte data relocations not supported");
    return ELF::R_MY_SIMULATOR_NONE;
  case FK_Data_2:
    Ctx.reportError(Fixup.getLoc(), "2-byte data relocations not supported");
    return ELF::R_MY_SIMULATOR_NONE;
  case FK_Data_4:
    if (Expr->getKind() == MCExpr::Target &&
        cast<MySimulatorMCExpr>(Expr)->getKind() == MySimulatorMCExpr::VK_MY_SIMULATOR_32_PCREL)
      return ELF::R_MY_SIMULATOR_32_PCREL;
    return ELF::R_MY_SIMULATOR_32;
  case FK_Data_8:
    return ELF::R_MY_SIMULATOR_64;
  case MySimulator::fixup_MY_SIMULATOR_hi20:
    return ELF::R_MY_SIMULATOR_HI20;
  case MySimulator::fixup_MY_SIMULATOR_lo12_i:
    return ELF::R_MY_SIMULATOR_LO12_I;
  case MySimulator::fixup_MY_SIMULATOR_lo12_s:
    return ELF::R_MY_SIMULATOR_LO12_S;
  case MySimulator::fixup_MY_SIMULATOR_tprel_hi20:
    return ELF::R_MY_SIMULATOR_TPREL_HI20;
  case MySimulator::fixup_MY_SIMULATOR_tprel_lo12_i:
    return ELF::R_MY_SIMULATOR_TPREL_LO12_I;
  case MySimulator::fixup_MY_SIMULATOR_tprel_lo12_s:
    return ELF::R_MY_SIMULATOR_TPREL_LO12_S;
  case MySimulator::fixup_MY_SIMULATOR_tprel_add:
    return ELF::R_MY_SIMULATOR_TPREL_ADD;
  case MySimulator::fixup_MY_SIMULATOR_relax:
    return ELF::R_MY_SIMULATOR_RELAX;
  case MySimulator::fixup_MY_SIMULATOR_align:
    return ELF::R_MY_SIMULATOR_ALIGN;
  case MySimulator::fixup_MY_SIMULATOR_set_6b:
    return ELF::R_MY_SIMULATOR_SET6;
  case MySimulator::fixup_MY_SIMULATOR_sub_6b:
    return ELF::R_MY_SIMULATOR_SUB6;
  case MySimulator::fixup_MY_SIMULATOR_add_8:
    return ELF::R_MY_SIMULATOR_ADD8;
  case MySimulator::fixup_MY_SIMULATOR_set_8:
    return ELF::R_MY_SIMULATOR_SET8;
  case MySimulator::fixup_MY_SIMULATOR_sub_8:
    return ELF::R_MY_SIMULATOR_SUB8;
  case MySimulator::fixup_MY_SIMULATOR_set_16:
    return ELF::R_MY_SIMULATOR_SET16;
  case MySimulator::fixup_MY_SIMULATOR_add_16:
    return ELF::R_MY_SIMULATOR_ADD16;
  case MySimulator::fixup_MY_SIMULATOR_sub_16:
    return ELF::R_MY_SIMULATOR_SUB16;
  case MySimulator::fixup_MY_SIMULATOR_set_32:
    return ELF::R_MY_SIMULATOR_SET32;
  case MySimulator::fixup_MY_SIMULATOR_add_32:
    return ELF::R_MY_SIMULATOR_ADD32;
  case MySimulator::fixup_MY_SIMULATOR_sub_32:
    return ELF::R_MY_SIMULATOR_SUB32;
  case MySimulator::fixup_MY_SIMULATOR_add_64:
    return ELF::R_MY_SIMULATOR_ADD64;
  case MySimulator::fixup_MY_SIMULATOR_sub_64:
    return ELF::R_MY_SIMULATOR_SUB64;
  }
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createMySimulatorELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<MySimulatorELFObjectWriter>(OSABI, Is64Bit);
}
