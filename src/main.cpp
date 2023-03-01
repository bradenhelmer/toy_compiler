#include "common.h"
#include "lexer.h"
#include "tokens.h"
#include <iostream>

int main(int argc, char **argv) {
  const char *test = "This is a test";
  Lexer lex = Lexer(test);
  Token *tok;
  for (int i = 0; i < 4; i++) {
    tok = lex.lexToken();
    tok->tokenOut();
  }
  return 0;
}
