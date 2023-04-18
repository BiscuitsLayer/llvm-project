//===-- MySimulatorTargetStreamer.cpp - MySimulator Target Streamer Methods -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides MySimulator specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "MySimulatorTargetStreamer.h"
#include "MySimulatorInfo.h"
#include "MySimulatorMCTargetDesc.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/MySimulatorAttributes.h"
#include "llvm/Support/MySimulatorISAInfo.h"

using namespace llvm;

MySimulatorTargetStreamer::MySimulatorTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}

void MySimulatorTargetStreamer::finish() { finishAttributeSection(); }

void MySimulatorTargetStreamer::emitDirectiveOptionPush() {}
void MySimulatorTargetStreamer::emitDirectiveOptionPop() {}
void MySimulatorTargetStreamer::emitDirectiveOptionPIC() {}
void MySimulatorTargetStreamer::emitDirectiveOptionNoPIC() {}
void MySimulatorTargetStreamer::emitDirectiveOptionRVC() {}
void MySimulatorTargetStreamer::emitDirectiveOptionNoRVC() {}
void MySimulatorTargetStreamer::emitDirectiveOptionRelax() {}
void MySimulatorTargetStreamer::emitDirectiveOptionNoRelax() {}
void MySimulatorTargetStreamer::emitAttribute(unsigned Attribute, unsigned Value) {}
void MySimulatorTargetStreamer::finishAttributeSection() {}
void MySimulatorTargetStreamer::emitTextAttribute(unsigned Attribute,
                                            StringRef String) {}
void MySimulatorTargetStreamer::emitIntTextAttribute(unsigned Attribute,
                                               unsigned IntValue,
                                               StringRef StringValue) {}

void MySimulatorTargetStreamer::emitTargetAttributes(const MCSubtargetInfo &STI) {
//   if (STI.hasFeature(MySimulator::FeatureRV32E))
//     emitAttribute(MySimulatorAttrs::STACK_ALIGN, MySimulatorAttrs::ALIGN_4);
//   else
    emitAttribute(MySimulatorAttrs::STACK_ALIGN, MySimulatorAttrs::ALIGN_16);

  unsigned XLen = 32;
  std::vector<std::string> FeatureVector;
  MySimulatorFeatures::toFeatureVector(FeatureVector, STI.getFeatureBits());

  auto ParseResult = llvm::MySimulatorISAInfo::parseFeatures(XLen, FeatureVector);
  if (!ParseResult) {
    /* Assume any error about features should handled earlier.  */
    consumeError(ParseResult.takeError());
    llvm_unreachable("Parsing feature error when emitTargetAttributes?");
  } else {
    auto &ISAInfo = *ParseResult;
    emitTextAttribute(MySimulatorAttrs::ARCH, ISAInfo->toString());
  }
}

// This part is for ascii assembly output
MySimulatorTargetAsmStreamer::MySimulatorTargetAsmStreamer(MCStreamer &S,
                                               formatted_raw_ostream &OS)
    : MySimulatorTargetStreamer(S), OS(OS) {}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionPush() {
  OS << "\t.option\tpush\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionPop() {
  OS << "\t.option\tpop\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionPIC() {
  OS << "\t.option\tpic\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionNoPIC() {
  OS << "\t.option\tnopic\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionRVC() {
  OS << "\t.option\trvc\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionNoRVC() {
  OS << "\t.option\tnorvc\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionRelax() {
  OS << "\t.option\trelax\n";
}

void MySimulatorTargetAsmStreamer::emitDirectiveOptionNoRelax() {
  OS << "\t.option\tnorelax\n";
}

void MySimulatorTargetAsmStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
  OS << "\t.attribute\t" << Attribute << ", " << Twine(Value) << "\n";
}

void MySimulatorTargetAsmStreamer::emitTextAttribute(unsigned Attribute,
                                               StringRef String) {
  OS << "\t.attribute\t" << Attribute << ", \"" << String << "\"\n";
}

void MySimulatorTargetAsmStreamer::emitIntTextAttribute(unsigned Attribute,
                                                  unsigned IntValue,
                                                  StringRef StringValue) {}

void MySimulatorTargetAsmStreamer::finishAttributeSection() {}
