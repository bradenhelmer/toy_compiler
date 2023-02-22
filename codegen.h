#include <llvm/IR/CallingConv.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IRPrinter/IRPrintingPasses.h>
/* #include <llvm/IR/ModuleProvider.h> */
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
/* #include <llvm/ExecutionEngine/JIT.h> */
#include <llvm/Support/raw_ostream.h>
#include <map>
#include <stack>

using namespace llvm;

class NBlock;

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;
    static llvm::LLVMContext* context;

public:
    Module *module;
    CodeGenContext() { module = new Module("main", *context); }

    static llvm::LLVMContext* getGlobalContext() { return context; }
    
    void generateCode(NBlock& root);
    GenericValue runCode();
    std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};
