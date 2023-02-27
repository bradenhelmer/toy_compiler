// tokens.h
// ~~~~~~~~
// Defines the registry of tokens.
#ifndef TOKENS_H
#define TOKENS_H

namespace tokdef {
// Macro magic for token enum
enum TokenType : unsigned short {
#define TOKEN(X) X,
#include "tokenDefs.h"
  NUM_TOKENS
};
const char *getTokenName(tokdef::TokenType type);
const char *getPunctuatorSeq(TokenType type);
} //namespace tokdef

class Token {
  tokdef::TokenType type;
  void *ptrVal;

public:
  // Default set token type to unknown
  Token() : type(tokdef::UNKNOWN) {}

  // Instantiate token with specified type
  Token(tokdef::TokenType type) : type(type) {}

  // Instantiate token with specified type and pointer to any associated
  // value the token holds E.G Token(tokdef::IDENTIFIER, ptrToIdentifierVal)
  template <typename T>
  Token(tokdef::TokenType type, T *ptrVal) : type(type), ptrVal(ptrVal) {}

  ~Token() {}

  tokdef::TokenType getType() { return type; }
  void setTokenType(tokdef::TokenType type) { this->type = type; }
  template <typename T> T *getPtrVal() { return this->ptrVal; }
  void resetToken() {
    this->type = tokdef::UNKNOWN;
    this->ptrVal = nullptr;
  }
};

#endif
