// parser.h
// ~~~~~~~~
// Parser class definition
#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
#include "lexer.h"
#include "tokens.h"

class Parser {
public:
  ast::NBlock *parseProgram();
  Parser(Lexer *lexer);

private:
  Token *tok;
  std::unique_ptr<ast::NBlock> root;
  Lexer *lexer;

  ast::NExpression *parseExpression();
  ast::NStatement *parseStatement();
  ast::NInteger *parseInteger();
  ast::NDouble *parseDouble();
  ast::NStrLiteral *parseStrLiteral();
  ast::NCharConstant *parseCharConstant();
  ast::NIdentifier *parseIdentifier();
  ast::NMethodCall *parseMethodCall();
  ast::NBinaryOperator *parseBinaryOperator();
  ast::NAssignment *parseAssignment();
  ast::NBlock *parseBlock();
  ast::NVariableDeclaration *parseVariableDeclaration();
  ast::NFunctionDeclaration *parseFunctionDeclaration();
};
#endif
