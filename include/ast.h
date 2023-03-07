#include <iostream>
#include <llvm/IR/Value.h>
#include <vector>

namespace ast {

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<std::unique_ptr<NStatement>> StatementList;
typedef std::vector<std::unique_ptr<NExpression>> ExpressionList;
typedef std::vector<std::unique_ptr<NVariableDeclaration>> VariableList;

class Node {
public:
  virtual ~Node() {}
  virtual llvm::Value *codeGen(CodeGenContext &context) {}
};

class NExpression : public Node {};

class NStatement : public Node {};

class NInteger : public NExpression {
public:
  long long value;
  NInteger(long long value) : value(value) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NDouble : public NExpression {
public:
  double value;
  NDouble(double value) : value(value) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NIdentifier : public NExpression {
public:
  std::string name;
  NIdentifier(const std::string &name) : name(name) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NMethodCall : public NExpression {
public:
  const std::unique_ptr<NIdentifier> &id;
  ExpressionList arguments;
  NMethodCall(const std::unique_ptr<NIdentifier> &id, ExpressionList &arguments)
      : id(id), arguments(arguments) {}
  NMethodCall(const std::unique_ptr<NIdentifier> &id) : id(id) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NBinaryOperator : public NExpression {
public:
  int op;
  std::unique_ptr<NExpression> &lhs;
  std::unique_ptr<NExpression> &rhs;
  NBinaryOperator(std::unique_ptr<NExpression> &lhs, int op,
                  std::unique_ptr<NExpression> &rhs)
      : lhs(lhs), rhs(rhs), op(op) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NAssignment : public NExpression {
public:
  std::unique_ptr<NIdentifier> &lhs;
  std::unique_ptr<NExpression> &rhs;
  NAssignment(std::unique_ptr<NIdentifier> &lhs,
              std::unique_ptr<NExpression> &rhs)
      : lhs(lhs), rhs(rhs) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NBlock : public NExpression {
public:
  StatementList statements;
  NBlock() {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NExpressionStatement : public NStatement {
public:
  std::unique_ptr<NExpression> &expression;
  NExpressionStatement(std::unique_ptr<NExpression> &expression)
      : expression(expression) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NVariableDeclaration : public NStatement {
public:
  const std::unique_ptr<NIdentifier> &type;
  std::unique_ptr<NIdentifier> &id;
  std::unique_ptr<NExpression> *assignmentExpr;
  NVariableDeclaration(const std::unique_ptr<NIdentifier> &type,
                       std::unique_ptr<NIdentifier> &id)
      : type(type), id(id) {}
  NVariableDeclaration(const std::unique_ptr<NIdentifier> &type,
                       std::unique_ptr<NIdentifier> &id,
                       std::unique_ptr<NExpression> *assignmentExpr)
      : type(type), id(id), assignmentExpr(assignmentExpr) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};

class NFunctionDeclaration : public NStatement {
public:
  const std::unique_ptr<NIdentifier> &type;
  const std::unique_ptr<NIdentifier> &id;
  VariableList arguments;
  std::unique_ptr<NBlock> &block;
  NFunctionDeclaration(const std::unique_ptr<NIdentifier> &type,
                       const std::unique_ptr<NIdentifier> &id,
                       const VariableList &arguments,
                       std::unique_ptr<NBlock> &block)
      : type(type), id(id), arguments(arguments), block(block) {}
  virtual llvm::Value *codeGen(CodeGenContext &context);
};
} // namespace ast
