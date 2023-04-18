//===-- MySimulatorMCObjectFileInfo.cpp - MySimulator object file properties ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the MySimulatorMCObjectFileInfo properties.
//
//===----------------------------------------------------------------------===//

#include "MySimulatorMCObjectFIleInfo.h"
#include "MySimulatorMCTargetDesc.h"
#include "llvm/MC/MCContext.h"

using namespace llvm;

unsigned MySimulatorMCObjectFileInfo::getTextSectionAlignment() const {
  const MCSubtargetInfo *STI = getContext().getSubtargetInfo();
  return 4;
}
