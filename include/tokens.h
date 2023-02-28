// tokens.h
// ~~~~~~~~
// Defines the registry of tokens.
#ifndef TOKENS_H
#define TOKENS_H
#include <string>

namespace tokdef {
// Macro magic for token enum
enum TokenType : unsigned short {
#define TOKEN(X) X,
#include "tokenDefs.h"
  NUM_TOKENS
};
const char *getTokenName(tokdef::TokenType type);
const char *getPunctuatorSeq(TokenType type);
} // namespace tokdef

class Token {
  tokdef::TokenType type;
  std::string *ptrVal;

public:
  // Default set token type to unknown
  Token() : type(tokdef::UNKNOWN) { ptrVal = nullptr; }

  // Instantiate token with specified type
  Token(tokdef::TokenType type) : type(type) {}

  // Instantiate token with specified type and pointer to any associated
  // value the token holds E.G Token(tokdef::IDENTIFIER, ptrToIdentifierVal)
  Token(tokdef::TokenType type, std::string *ptrVal)
      : type(type), ptrVal(ptrVal) {}

  ~Token() {}

  tokdef::TokenType getType() { return type; }
  void setTokenType(tokdef::TokenType type) { this->type = type; }
  std::string *getPtrVal() { return this->ptrVal; }
  void setPtrVal(std::string *val) {
    if (ptrVal != nullptr)
      delete ptrVal;
  }
  void resetToken() {
    this->type = tokdef::UNKNOWN;
    this->ptrVal = nullptr;
  }
};

#endif
