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

  std::unique_ptr<ast::NExpression> parseExpression();
  std::unique_ptr<ast::NStatement> parseStatement();
  std::unique_ptr<ast::NInteger> parseInteger();
  std::unique_ptr<ast::NInteger> parseDouble();
  std::unique_ptr<ast::NIdentifier> parseIdentifier();
  std::unique_ptr<ast::NMethodCall> parseMethodCall();
  std::unique_ptr<ast::NBinaryOperator> parserBinaryOperator();
  std::unique_ptr<ast::NAssignment> parseAssignment();
  std::unique_ptr<ast::NBlock> parseBlock();
  std::unique_ptr<ast::NVariableDeclaration> parseVariableDeclaration();
  std::unique_ptr<ast::NFunctionDeclaration> parseFunctionDeclatration();

};
#endif
