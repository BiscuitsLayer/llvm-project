//===-- MySimulatorMCObjectFileInfo.h - MySimulator object file Info -------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the MySimulatorMCObjectFileInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MySimulatorMCOBJECTFILEINFO_H
#define LLVM_LIB_TARGET_MY_SIMULATOR_MCTARGETDESC_MySimulatorMCOBJECTFILEINFO_H

#include "llvm/MC/MCObjectFileInfo.h"

namespace llvm {

class MySimulatorMCObjectFileInfo : public MCObjectFileInfo {
public:
  unsigned getTextSectionAlignment() const override;
};

} // namespace llvm

#endif
