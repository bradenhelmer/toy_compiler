// lexer.cpp
// ~~~~~~~
// This file implements the lexer interface
#include "common.h"
#include "lexer.h"
#include "token_buff.h"
#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include <memory>

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
  TEST_OUT("TEST");
  // Skipping comments and whitespace.
  if (*srcBuffer == '#')
    skipComment();
  if (isspace(*srcBuffer))
    skipWhiteSpace();

  // First we need to check if the next token could potentially be an identifier
  if (*srcBuffer == '_' || isalpha(*srcBuffer)) {
    TokenBuffer tokBuf = TokenBuffer();
    do {
      tokBuf.append(*srcBuffer);
      srcBuffer++;
    } while (*srcBuffer == '_' || isalnum(*srcBuffer));
    curToken.setTokenType(tokdef::ID);
    curToken.setPtrVal(new std::string(tokBuf.str()));
    return &curToken;
  }

  if (isdigit(*srcBuffer)) {
    lexNumericLiteral();
    return &curToken;
  }
}

void Lexer::lexNumericLiteral() {
  TokenBuffer tokBuf = TokenBuffer();
  bool hasDot = false;
  do {
    tokBuf.append(*srcBuffer);
    if (*srcBuffer == '.' && hasDot) {
      curToken.setTokenType(tokdef::ERROR);
      curToken.setPtrVal(new std::string(
          "Only one decimal place allowed in numeric literal!"));
      return;
    } else if (*srcBuffer == '.') {
      hasDot = true;
    }
    srcBuffer++;
  } while (!isspace(*srcBuffer));
  curToken.setTokenType(hasDot ? tokdef::FP : tokdef::INT);
  curToken.setPtrVal(new std::string(tokBuf.str()));
}

void Lexer::lexStringLiteral() {}
