
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
struct LoopCounterPass : public LoopPass {
    static char ID; // Pass identification, replacement for typeid
    LoopCounterPass()
        : LoopPass(ID)
    {
    }

    virtual bool runOnLoop(Loop* L, LPPassManager& LPM)
    {
        outs() << "Loop info:"
               << "\n";
        outs() << *L << "\n";
        outs() << "Depth: " << L->getLoopDepth() << "\n";
        outs() << "Is innermost: " << L->isInnermost() << "\n";
        outs() << "Blocks number: " << L->getNumBlocks() << "\n";
        outs() << "Is guarded: " << L->isGuarded() << "\n";

        bool isCountable = getAnalysis<ScalarEvolutionWrapperPass>()
                               .getSE()
                               .hasLoopInvariantBackedgeTakenCount(L);
        if (!isCountable) {
            outs() << "Cannot count number of iterations"
                   << "\n";
        } else {
            auto LoopIterNum = getAnalysis<ScalarEvolutionWrapperPass>()
                                   .getSE()
                                   .getBackedgeTakenCount(L);
            outs() << "Precalculated number of iterations: ";
            LoopIterNum->print(outs());
            outs() << "\n";
        }

        return false;
    }

    void getAnalysisUsage(AnalysisUsage& AU) const override
    {
        AU.addRequired<LoopInfoWrapperPass>();
        AU.addPreserved<LoopInfoWrapperPass>();
        AU.addRequired<ScalarEvolutionWrapperPass>();
        AU.addPreserved<ScalarEvolutionWrapperPass>();
        AU.setPreservesAll();
    }
};

} // namespace

char LoopCounterPass::ID = 0;

static void RegisterLoopCounterPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
  PM.add(new LoopCounterPass());
}
static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, RegisterLoopCounterPass);

// static RegisterPass<LoopCounterPass> X("loopcounter", "Loop Counter Pass",
//     false /* Only looks at CFG */,
//     true /* Analysis Pass */);

