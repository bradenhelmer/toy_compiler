#include "codegen.h"
#include "node.h"
#include "parser.hpp"

void CodeGenContext::generateCode(NBlock &root) {}
llvm::GenericValue CodeGenContext::runCode() {}

static const llvm::Type *typeOf(const NIdentifier &type) {
  if (type.name.compare("int") == 0) {
    return llvm::Type::getInt64Ty(CodeGenContext::getGlobalContext());
  } else if (type.name.compare("double") == 0) {
    return llvm::Type::getDoubleTy(CodeGenContext::getGlobalContext());
  }
  return llvm::Type::getVoidTy(CodeGenContext::getGlobalContext());
}

llvm::Value *NInteger::codeGen(CodeGenContext &context) {
  std::cout << "Creating integer: " << value << std::endl;
  return llvm::ConstantInt::get(
      llvm::Type::getInt64Ty(CodeGenContext::getGlobalContext()), value, true);
}

llvm::Value *NDouble::codeGen(CodeGenContext &context) {
  std::cout << "Creating double: " << value << std::endl;
  return llvm::ConstantFP::get(
      llvm::Type::getDoubleTy(CodeGenContext::getGlobalContext()), value);
}

llvm::Value *NIdentifier::codeGen(CodeGenContext &context) {}
llvm::Value *NMethodCall::codeGen(CodeGenContext &context) {}
llvm::Value *NBinaryOperator::codeGen(CodeGenContext &context) {}
llvm::Value *NAssignment::codeGen(CodeGenContext &context) {}
llvm::Value *NBlock::codeGen(CodeGenContext &context) {}
llvm::Value *NExpressionStatement::codeGen(CodeGenContext &context) {}
llvm::Value *NVariableDeclaration::codeGen(CodeGenContext &context) {}
llvm::Value *NFunctionDeclaration::codeGen(CodeGenContext &context) {}
