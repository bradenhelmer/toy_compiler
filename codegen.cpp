#include "codegen.h"
#include "node.h"
#include "parser.hpp"

void CodeGenContext::generateCode(NBlock &root) {}
llvm::GenericValue CodeGenContext::runCode() {}

static llvm::Type *typeOf(const NIdentifier &type) {
  if (type.name.compare("int") == 0) {
    return llvm::Type::getInt64Ty(CodeGenContext::getGlobalContext());
  } else if (type.name.compare("double") == 0) {
    return llvm::Type::getDoubleTy(CodeGenContext::getGlobalContext());
  } else if (type.name.compare("void") == 0) {
    return llvm::Type::getVoidTy(CodeGenContext::getGlobalContext());
  }
  return NULL;
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

llvm::Value *NIdentifier::codeGen(CodeGenContext &context) {
  std::cout << "Creating identifier reference: " << name << std::endl;
  if (context.locals().find(name) == context.locals().end()) {
    std::cerr << "Undeclared variable" << name << std::endl;
    return NULL;
  }
  llvm::Value *V = context.locals()[name];
  return new llvm::LoadInst(V->getType(), V, "", false, context.currentBlock());
}

llvm::Value *NMethodCall::codeGen(CodeGenContext &context) {
  llvm::Function *FUNCTION = context.module->getFunction(id.name.c_str());
  std::vector<llvm::Value *> args;
  ExpressionList::const_iterator it;
  for (it = arguments.begin(); it != arguments.end(); it++) {
    args.push_back((**it).codeGen(context));
  }
  std::cout << "Creating method call: " << id.name << std::endl;
  llvm::CallInst *CALL =
      llvm::CallInst::Create(FUNCTION->getFunctionType(), FUNCTION, args,
                             id.name, context.currentBlock());
  return CALL;
}

llvm::Value *NBinaryOperator::codeGen(CodeGenContext &context) {
  std::cout << "Creating binary operation : " << op << std::endl;
  llvm::Instruction::BinaryOps instr;
  switch (op) {
  case TPLUS:
    instr = llvm::Instruction::Add;
    goto math;
  case TMINUS:
    instr = llvm::Instruction::Sub;
    goto math;
  case TMUL:
    instr = llvm::Instruction::Mul;
    goto math;
  case TDIV:
    instr = llvm::Instruction::SDiv;
    goto math;
  }
  return NULL;
math:
  return llvm::BinaryOperator::Create(instr, lhs.codeGen(context),
                                      rhs.codeGen(context), "",
                                      context.currentBlock());
}
llvm::Value *NAssignment::codeGen(CodeGenContext &context) {
  std::cout << "Creating assignment for " << lhs.name << std::endl;
  if (context.locals().find(lhs.name) == context.locals().end()) {
    std::cerr << "Undeclared variable" << lhs.name << std::endl;
    return NULL;
  }
  llvm::Value *LHSVAL = context.locals()[lhs.name];
  return new llvm::StoreInst(rhs.codeGen(context), LHSVAL, false,
                             context.currentBlock());
}
llvm::Value *NBlock::codeGen(CodeGenContext &context) {
  StatementList::const_iterator it;
  llvm::Value *LAST = NULL;
  for (it = statements.begin(); it != statements.end(); it++) {
    std::cout << "Generating code for " << typeid(**it).name() << std::endl;
    LAST = (**it).codeGen(context);
  }
  std::cout << "Creating block..." << std::endl;
  return LAST;
}
llvm::Value *NExpressionStatement::codeGen(CodeGenContext &context) {
  std::cout << "Generating code for " << typeid(expression).name() << std::endl;
  return expression.codeGen(context);
}
llvm::Value *NVariableDeclaration::codeGen(CodeGenContext &context) {
  std::cout << "Creating variable declaration " << type.name << " " << id.name
            << std::endl;
  llvm::Type *VARTYPE = typeOf(type);
  if (VARTYPE == NULL) {
    std::cerr << "Undefined type: " << type.name << std::endl;
    return NULL;
  } else if (VARTYPE->getTypeID() == llvm::Type::VoidTyID) {
    std::cerr << "Cannot declare variable as void" << std::endl;
    return NULL;
  }
  llvm::Type *TYPE = typeOf(type);
  llvm::AllocaInst *ALLOC =
      new llvm::AllocaInst(TYPE, TYPE->getPointerAddressSpace(),
                           id.name.c_str(), context.currentBlock());
}

llvm::Value *NFunctionDeclaration::codeGen(CodeGenContext &context) {
  std::vector<llvm::Type *> argTypes;
  VariableList::const_iterator it;
  for (it = arguments.begin(); it != arguments.end(); it++) {
    argTypes.push_back(typeOf((**it).type));
  }
  llvm::FunctionType *FTYPE =
      llvm::FunctionType::get(typeOf(type), argTypes, false);
  llvm::Function *FUNCTION =
      llvm::Function::Create(FTYPE, llvm::GlobalValue::InternalLinkage,
                             id.name.c_str(), context.module);
  llvm::BasicBlock *BBBLOCK = llvm::BasicBlock::Create(
      CodeGenContext::getGlobalContext(), "entry", FUNCTION, 0);
  context.pushBlock(BBBLOCK);

  for (it = arguments.begin(); it != arguments.end(); it++) {
    (**it).codeGen(context);
  }
  block.codeGen(context);
  llvm::ReturnInst::Create(CodeGenContext::getGlobalContext(), BBBLOCK);
  context.popBlock();
  std::cout << "Creating function: " << id.name << std::endl;
  return FUNCTION;
}
