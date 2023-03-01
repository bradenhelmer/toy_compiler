// lexer.cpp
// ~~~~~~~
// This file implements the lexer interface
#include "lexer.h"
#include "common.h"
#include "token_buff.h"
#include <cstring>
#include <iostream>

Lexer::Lexer(const char *srcBuffer) : srcBuffer(srcBuffer) {
  curToken = Token();
}

void Lexer::skipWhiteSpace() {
  while (isspace(*srcBuffer))
    srcBuffer++;
}

void Lexer::skipComment() {
  do {
    srcBuffer++;
  } while (*srcBuffer != '\n');
  srcBuffer++;
}

Token *Lexer::lexToken() {
  // Assuming parser has already used the token, we can reset its values here.
  curToken.resetToken();

  // Skipping comments and whitespace.
  if (*srcBuffer == '#')
    skipComment();
  if (isspace(*srcBuffer))
    skipWhiteSpace();

  // First we need to check if the next token could potentially be an identifier
  if (*srcBuffer == '_' || isalpha(*srcBuffer)) {

    // Set token type to identifier and create new token buffer
    curToken.setTokenType(tokdef::ID);
    TokenBuffer tokBuf = TokenBuffer();

    // Traverse identifier and store in token buffer.
    do {
      tokBuf.append(*srcBuffer);
      srcBuffer++;
    } while (*srcBuffer == '_' || isalnum(*srcBuffer));

    srcBuffer++;

    std::string *id = new std::string;
    *id = tokBuf.str();
    curToken.setPtrVal(id);
    return &curToken;
  }

  if (isdigit(*srcBuffer)) {
    lexNumericLiteral();
    return &curToken;
  }

  if (*srcBuffer == EOF || *srcBuffer == '\0')
    curToken.setTokenType(tokdef::EoF);
  return &curToken;
}

void Lexer::lexNumericLiteral() {
  TokenBuffer tokBuf = TokenBuffer();
  bool hasDot = false;

  // Build numeric literal
  do {
    tokBuf.append(*srcBuffer);
    // Check if token has more than one decimal place
    if (*srcBuffer == '.' && hasDot) {
      curToken.setTokenType(tokdef::ERROR);
      curToken.setPtrVal(new std::string(
          "Only one decimal place allowed in numeric literal!"));
      return;
    } else if (*srcBuffer == '.') {
      hasDot = true;
    }
    srcBuffer++;
  } while (!isspace(*srcBuffer) || isdigit(*srcBuffer) || *srcBuffer == '.');
  curToken.setTokenType(hasDot ? tokdef::FP : tokdef::INT);
  curToken.setPtrVal(new std::string(tokBuf.str()));
}

void Lexer::lexStringLiteral() {}
