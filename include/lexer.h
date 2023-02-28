// lexer.h
// ~~~~~~~
// This file defines the lexer interface
#ifndef LEXER_H
#define LEXER_H
#include "tokens.h"

class Lexer {

  const char *srcBuffer;
  Token curToken;

public:
  Lexer(const char *srcBuffer);
  void skipWhiteSpace();
  void skipComment();
  Token *lexToken();
  void lexStringLiteral();
  void lexNumericLiteral();
};
#endif
