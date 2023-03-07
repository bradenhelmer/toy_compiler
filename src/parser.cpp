// parser.cpp
// ~~~~~~~~~~
// Implementation of parser class
#include "parser.h"

Parser::Parser(Lexer *lexer) : lexer(lexer) {
  tok = new Token();
  root = new ast::NBlock();
}
