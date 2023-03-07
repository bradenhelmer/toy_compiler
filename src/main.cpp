#include "common.h"
#include "lexer.h"
#include "tokens.h"
#include "utils.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

  /* const char *file_contents = readFileIntoBuffer("../test/test_src.txt"); */
  const char* program = "int do_math(int a) { \"dookie\" x > a * 5 + 3 } do_math(34)";
  Lexer *lex = new Lexer(program);
  std::cout << "BEGIN OUTPUT\n------------\n";
  std::cout << "Lexing: \n" << program << std::endl << std::endl;
  Token *tok = lex->lexToken();
  while (tok->getType() != tokdef::EoF) {
    tok->tokenOut();
    tok = lex->lexToken();
  }

  std::cout << "------------\nEND OUTPUT\n";
  return 0;
}
