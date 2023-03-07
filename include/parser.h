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

  void parseExpression();
  void parseStatement();
  void parserIdentifier();
  void parseMethodCall();
  void parserBinaryOperator();
  void parseAssignment();
  void parseBlock();
  void parseExpressionStatement();
  void parseVariableDeclaration();
  void parseFunctionDeclatration();

};
#endif
