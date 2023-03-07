#include "common.h"
#include "lexer.h"
#include "tokens.h"
#include "utils.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

  /* const char *file_contents = readFileIntoBuffer("../test/test_src.txt"); */

  Lexer *lex = new Lexer("int do_math(int a) { int x = a * 5 + 3 } do_math(34)");
  std::cout << "BEGIN OUTPUT\n------------\n";
  Token *tok = lex->lexToken();
  while (tok->getType() != tokdef::EoF) {
    tok->tokenOut();
    tok = lex->lexToken();
  }

  std::cout << "------------\nEND OUTPUT\n";
  return 0;
}
