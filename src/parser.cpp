// parser.cpp
// ~~~~~~~~~~
// Implementation of parser class
#include "parser.h"

Parser::Parser(Lexer *lexer) : lexer(lexer) {
  tok = new Token();
  root = std::make_unique<ast::NBlock>();
}

std::unique_ptr<ast::NInteger> Parser::parseInteger() {
  // Assertion that the current token is of type integer,
  // this function should be called if a tokdef::INT is encountered.
  assert(tok->getType() == tokdef::INT);

  // Get pointer val from the token an convert to integer
  // and eat next token
  int val = std::stoi(tok->getPtrVal());
  tok = lexer->lexToken();

  // Create pointer for new ast node and return
  std::unique_ptr<ast::NInteger> result = std::make_unique<ast::NInteger>(val);
  return std::move(result);
}

std::unique_ptr<ast::NDouble> Parser::parseDouble() {
  // Assertion that the current token is of type double or floating point,
  // this function should be called if a tokdef::FP is encountered.
  assert(tok->getType() == tokdef::FP);

  // Get pointer val from the token an convert to double
  // and eat next token
  double val = std::stod(tok->getPtrVal());
  tok = lexer->lexToken();

  // Create pointer for new ast node and return
  std::unique_ptr<ast::NDouble> result = std::make_unique<ast::NDouble>(val);
  return std::move(result);
}

std::unique_ptr<ast::NIdentifier> Parser::parseIdentifier() {
  assert(tok->getType() == tokdef::ID);
  std::unique_ptr<ast::NIdentifier> result =
      std::make_unique<ast::NIdentifier>(tok->getPtrVal());
  tok = lexer->lexToken();
  return std::move(result);
}

