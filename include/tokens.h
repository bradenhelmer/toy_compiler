// tokens.h
// ~~~~~~~~
// Defines the registry of tokens.
#ifndef TOKENS_H
#define TOKENS_H

namespace tokdef {

enum TokenType : unsigned short {
#define TOKEN(X) X,
#include "tokenDefs.h"
  NUM_TOKENS
};
const char *getTokenName(TokenType type);
const char *getPunctuatorSeq(TokenType type);
} // namespace tokdef

class Token {
public:
};

#endif
