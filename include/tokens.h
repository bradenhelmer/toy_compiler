// tokens.h
// ~~~~~~~~
// Defines the registry of tokens.
#ifndef TOKENS_H
#define TOKENS_H
#include "common.h"
#include <iostream>
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

// Token class: Holds a TokenType enum value for the parser to used
// Additionally holds a
class Token {
    const char* lexOut = "Lexed Token: ";

private:
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

  ~Token() { delete ptrVal; }

  // Getters for ptrval and token type
  std::string getPtrVal() const { return *ptrVal; }
  tokdef::TokenType getType() const { return type; }

  // Pretty prints token
  void tokenOut() const {
    if (isIdentifier() || isLiteralOrNumeric()) {
      std::cout << lexOut << getPtrVal() << " (" << tokdef::getTokenName(type)
                << ")" << std::endl;
    } else if (isPunctuator()) {
      std::cout << lexOut << tokdef::getPunctuatorSeq(type) << " ("
                << tokdef::getTokenName(type) << ")" << std::endl;
    } else {
      std::cout << lexOut << tokdef::getTokenName(type) << std::endl;
    }
  }

  // Resets token
  void resetToken() {
    this->type = tokdef::UNKNOWN;
    ptrVal = nullptr;
  }
  void setPtrVal(std::string *val) { ptrVal = val; }
  void setTokenType(tokdef::TokenType type) { this->type = type; }

  // Token info checkers
  bool isIdentifier() const { return type == tokdef::ID; }
  bool isLiteralOrNumeric() const {
    return type == tokdef::INT || type == tokdef::FP ||
           type == tokdef::STRLITERAL;
  }
  bool isPunctuator() const {
    return tokdef::ASSIGN <= type && type <= tokdef::DIV;
  }
};

#endif
