// lexer.cpp
// ~~~~~~~~~
// This file implements the lexer interface
#include "lexer.h"
#include "common.h"
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

  // Check for numeric literal
  if (isdigit(curChar)) {
    return lexNumericLiteral();
  }

  // Check for possible identifier
  if (curChar == '_' || isalpha(curChar)) {
    curToken->setTokenType(tokdef::ID);
    std::string *id = new std::string;
    do {
      *id += *srcBuffer;
      ++srcBuffer;
    } while (isalnum(*srcBuffer) || *srcBuffer == '_');
    curToken->setPtrVal(id);
    return curToken;
  }

  if (curChar == '#')
    skipComment();

  switch (curChar) {
  case 0:
    curToken->setTokenType(tokdef::EoF);
    break;
  case '.':
    curToken->setTokenType(tokdef::DOT);
    break;
  case ',':
    curToken->setTokenType(tokdef::COMMA);
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
      curToken->setTokenType(tokdef::GREATERTHAN);
    }
    break;
  case '"':
    return lexStringLiteral();
  }

  // At this point, we can assume that we have lexed a successful token and
  // advance the pointer to the next position. Except for an EoF
  if (curToken->getType() != tokdef::EoF)
    ++srcBuffer;
  return curToken;
}

Token *Lexer::lexNumericLiteral() {
  bool hasDot = false;
  std::string *num = new std::string;
  do {
    if (*srcBuffer == '.') {
      if (hasDot) {
        curToken->setTokenType(tokdef::ERROR);
        curToken->setPtrVal(new std::string(
            "Numeric constants may only contain one decimal point!"));
        return curToken;
      }
      hasDot = true;
    }
    *num += *srcBuffer;
    ++srcBuffer;
  } while (isdigit(*srcBuffer) || *srcBuffer == '.');
  ++srcBuffer;
  curToken->setTokenType(hasDot ? tokdef::FP : tokdef::INT);
  curToken->setPtrVal(num);
  return curToken;
}

Token *Lexer::lexStringLiteral() {
  curToken->setTokenType(tokdef::STRLITERAL);
  std::string *literal = new std::string;
  ++srcBuffer;
  while (*srcBuffer != '"') {
    *literal += *srcBuffer;
    ++srcBuffer;
  }
  ++srcBuffer;
  curToken->setPtrVal(literal);
  return curToken;
}
