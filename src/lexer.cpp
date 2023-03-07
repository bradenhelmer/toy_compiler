// lexer.cpp
// ~~~~~~~~~
// This file implements the lexer interface
#include "lexer.h"
#include "common.h"
#include "token_buff.h"
#include <iostream>

Lexer::Lexer(const char *srcBuffer) : srcBuffer(srcBuffer) {
  curToken = new Token();
}

void Lexer::skipWhiteSpace() {
  while (isspace(*srcBuffer))
    ++srcBuffer;
}

void Lexer::skipComment() {
  do {
    ++srcBuffer;
  } while (*srcBuffer != '\n');
  ++srcBuffer;
}

Token *Lexer::lexToken() {
  // Reset token values
  curToken->resetToken();

  // First, advance through whitespace
  if (isspace(*srcBuffer))
    skipWhiteSpace();

  // Get character at buffer
  const char curChar = *srcBuffer;
  
  // Check for possible identifier
  if (curChar == '_' || isalnum(curChar)) {
    curToken->setTokenType(tokdef::ID);
    TokenBuffer tokBuf = TokenBuffer();
    do {
      tokBuf.append(*srcBuffer);
      ++srcBuffer;
    } while (isalnum(*srcBuffer) || *srcBuffer == '_');
    ++srcBuffer;
    std::string *id = new std::string(tokBuf.str());
    curToken->setPtrVal(id);
    return curToken;
  }

  // Check for numeric literaliteral
  if (isdigit(curChar))
    return lexNumericLiteral();

  if (curChar == '#')
    skipComment();

  switch (curChar) {
  case 0:
    curToken->setTokenType(tokdef::EoF);
    break;
  case '(':
    curToken->setTokenType(tokdef::LPAREN);
    break;
  case ')':
    curToken->setTokenType(tokdef::RPAREN);
    break;
  case '{':
    curToken->setTokenType(tokdef::LBRACE);
    break;
  case '}':
    curToken->setTokenType(tokdef::RBRACE);
    break;
  case '-':
    curToken->setTokenType(tokdef::MINUS);
    break;
  case '+':
    curToken->setTokenType(tokdef::PLUS);
    break;
  case '*':
    curToken->setTokenType(tokdef::MULT);
    break;
  case '/':
    curToken->setTokenType(tokdef::DIV);
    break;
  case '=':
    if (peek() == '=') {
      ++srcBuffer;
      curToken->setTokenType(tokdef::EQUAL);
    } else {
      curToken->setTokenType(tokdef::ASSIGN);
    }
    break;
  case '!':
    if (peek() == '=') {
      ++srcBuffer;
      curToken->setTokenType(tokdef::NOTEQUAL);
    }
    break;
  case '<':
    if (peek() == '=') {
      ++srcBuffer;
      curToken->setTokenType(tokdef::LESSEQUALTHAN);
    } else {
      curToken->setTokenType(tokdef::LESSTHAN);
    }
    break;
  case '>':
    if (peek() == '=') {
      ++srcBuffer;
      curToken->setTokenType(tokdef::GREATEREQUALTHAN);
    } else {
      curToken->setTokenType(tokdef::GREATEREQUALTHAN);
    }
    break;
  }

  // At this point, we can assume that we have lexed a successful token and
  // advance the pointer to the next position. Except for an EoF
  /* if (curToken->getType() != tokdef::EoF) */
    ++srcBuffer;
  return curToken;
}

Token *Lexer::lexNumericLiteral() {}

Token *Lexer::lexStringLiteral() {}
