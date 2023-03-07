// lexer.h
// ~~~~~~~
// This file defines the lexer interface
#ifndef LEXER_H
#define LEXER_H
#include "tokens.h"

class Lexer {

public:
  Lexer(const char *srcBuffer);
  void skipWhiteSpace();
  void skipComment();
  Token *lexToken();
  Token *lexStringLiteral();
  Token *lexNumericLiteral();
  bool isAtEnd() const { return *srcBuffer == '\0'; }
  const char peek() const { return *(srcBuffer + 1); }

private:
  const char *srcBuffer;
  Token *curToken;
};
#endif
