// parser.cpp
// ~~~~~~~~~~
// Implementation of parser class
#include "parser.h"

Parser::Parser(Lexer &lexer) : lexer(lexer) {
  tok = new Token();
  root = new ast::NBlock();
}

ast::NExpression *Parser::parseExpression() {}
ast::NStatement *Parser::parseStatement() {}

ast::NInteger *Parser::parseInteger() {
  // Assertion that the current token is of type integer,
  // this function should be called if a tokdef::INT is encountered.
  assert(tok->getType() == tokdef::INT);

  // Get pointer val from the token an convert to integer
  // and eat next token
  int val = std::stoi(tok->getPtrVal());
  tok = lexer.lexToken();

  // Create pointer for new ast node and return
  ast::NInteger *result = new ast::NInteger(val);
  return result;
}

ast::NDouble *Parser::parseDouble() {
  // Assertion that the current token is of type double or floating point,
  // this function should be called if a tokdef::FP is encountered.
  assert(tok->getType() == tokdef::FP);

  // Get pointer val from the token an convert to double
  // and eat next token
  double val = std::stod(tok->getPtrVal());
  tok = lexer.lexToken();

  // Create pointer for new ast node and return
  ast::NDouble *result = new ast::NDouble(val);
  return result;
}

ast::NStrLiteral *Parser::parseStrLiteral() {}
ast::NCharConstant *Parser::parseCharConstant() {}

ast::NIdentifier *Parser::parseIdentifier() {
  assert(tok->getType() == tokdef::ID);
  ast::NIdentifier *result = new ast::NIdentifier(tok->getPtrVal());
  tok = lexer.lexToken();
  return result;
}

ast::NMethodCall *Parser::parseMethodCall() {}
ast::NBinaryOperator *Parser::parseBinaryOperator() {}
ast::NAssignment *Parser::parseAssignment() {}
ast::NBlock *Parser::parseBlock() {}
ast::NVariableDeclaration *Parser::parseVariableDeclaration() {}
ast::NFunctionDeclaration *Parser::parseFunctionDeclaration() {}
