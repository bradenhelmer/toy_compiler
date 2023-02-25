// tokens.cpp
// ~~~~~~~~~~
// Implements token interface
#include "../include/tokens.h"

static const char *const TokenNames[] = {
#define TOKEN(X) #X,
#include "../include/tokenDefs.h"
    nullptr};

inline const char *tokdef::getTokenName(TokenType type) {
  return type < NUM_TOKENS ? TokenNames[type] : nullptr;
}

const char *tokdef::getPunctuatorSeq(TokenType type) {
  switch (type) {
#define TOKEN_PUNCTUATOR(NAME, SEQ)                                            \
  case NAME:                                                                   \
    return SEQ;
#include "../include/tokenDefs.h"
  default:
    break;
  }
  return nullptr;
}
