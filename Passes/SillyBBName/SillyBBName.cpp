//===-- HelloWorld.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SillyBBName.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <random>

using namespace llvm;

const char *adjectives[] = {
	"",
	"antsy", "blind", "crafty", "dreary", "eloquent",
	"fast", "green", "hefty", "ignoble", "jaunty",
	"krufty", "lewd", "minor", "nice", "old",
	"poor", "quiet", "red", "stoic", "taut",
	"ugly", "vibrant", "waning", "extreme",
	"young", "zonky"
};

const char *nouns[] = {
	"Adam", "Bag", "Cobra", "Dude", "Eve",
	"Frog", "Ghost", "Hat", "Ide", "Jug",
	"Keg", "Lug", "Maid", "Night", "Oort",
	"Pig", "Quag", "Rag", "Stupor", "Tug",
	"Uzi", "Velo", "Wheat", "Oxo",
	"Yurt", "Zag"
};

PreservedAnalyses SillyBBName::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  for(Function::iterator it=F.begin(); it!=F.end(); ++it) {
    // iterate through basic blocks
    errs() << F.getName() << "::";
    errs() << adjectives[(rand() % 27)] << " " << nouns[(rand() % 26)];
    errs() << "\n";
  }
  return PreservedAnalyses::all();
}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
PassPluginLibraryInfo getPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "SillyBBName", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "sbbname") {
                    FPM.addPass(SillyBBName());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getPluginInfo();
}
