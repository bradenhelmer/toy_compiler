// tokens.cpp
// ~~~~~~~~~~
// Implements token interface
#include "tokens.h"

static const char *const TokenNames[] = {
#define TOKEN(X) #X,
#include "../include/tokenDefs.h"
    nullptr};

const char *tokdef::getTokenName(tokdef::TokenType type) {
  return type < tokdef::NUM_TOKENS ? TokenNames[type] : nullptr;
}

const char *tokdef::getPunctuatorSeq(tokdef::TokenType type) {
  switch (type) {
#define TOKEN_PUNCTUATOR(NAME, SEQ)                                            \
case tokdef::NAME:                                                                   \
    return SEQ;
#include "../include/tokenDefs.h"
  default:
    break;
  }
  return nullptr;
}
