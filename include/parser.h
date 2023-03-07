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
  ast::NBlock *root;
  Lexer *lexer;

};
#endif
