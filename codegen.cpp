#include "node.h"
#include "codegen.h"
#include "parser.hpp"

void CodeGenContext::generateCode(NBlock &root){}
llvm::GenericValue CodeGenContext::runCode() {}
static const llvm::Type *typeOf(const NIdentifier& type) {}
llvm::Value* NInteger::codeGen(CodeGenContext &context) {}
llvm::Value* NDouble::codeGen(CodeGenContext &context) {}
llvm::Value* NIdentifier::codeGen(CodeGenContext &context) {}
llvm::Value* NMethodCall::codeGen(CodeGenContext &context) {}
llvm::Value* NBinaryOperator::codeGen(CodeGenContext &context) {}
llvm::Value* NAssignment::codeGen(CodeGenContext &context) {}
llvm::Value* NBlock::codeGen(CodeGenContext &context) {}
llvm::Value* NExpressionStatement::codeGen(CodeGenContext &context) {}
llvm::Value* NVariableDeclaration::codeGen(CodeGenContext &context) {}
llvm::Value* NFunctionDeclaration::codeGen(CodeGenContext &context) {}

