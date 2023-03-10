#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

class TestPass final : public PassInfoMixin<TestPass> {
public:
  PreservedAnalyses run([[maybe_unused]] Module &M, ModuleAnalysisManager &) {
    outs() << "Passo di test per il corso di Linguaggi e Compilatori"
           << "\n";

    for(auto iter=M.begin(); iter!=M.end(); ++iter){
      Function &F = *iter;
      outs() << F.getName() << "\n" << "Numero di argomenti: " << F.arg_size() << "\n";
      
      int n_basicblock = 0;
      int n_istruzioni = 0;

      for(BasicBlock &BB : F){
        n_basicblock += 1;
        n_istruzioni += BB.size();
      }  
      
      // outs() << "N (name=" << BB.getName() << " has " << BB.size() << "instruction \t";


      outs() << "numero di Basic Block: " << n_basicblock <<"\n" << "Numero di istruzioni: "<< n_istruzioni <<"\n\n";


    }
      // TODO: Completare il metodo come indicato per il LAB1.
    
    //}

    return PreservedAnalyses::all();
  }
}; // class TestPass

} // anonymous namespace

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
      .APIVersion = LLVM_PLUGIN_API_VERSION,
      .PluginName = "TestPass",
      .PluginVersion = LLVM_VERSION_STRING,
      .RegisterPassBuilderCallbacks =
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) -> bool {
                  if (Name == "test-pass") {
                    MPM.addPass(TestPass());
                    return true;
                  }
                  return false;
                });
          } 
  };
}
