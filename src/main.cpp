#include <iostream>
#include "tokens.h"

int main(int argc, char **argv) {

  for (int type = tokdef::UNKNOWN; type < tokdef::NUM_TOKENS; type++) {
        tokdef::TokenType TYPE = static_cast<tokdef::TokenType>(type); 
        std::cout << *tokdef::getTokenName(TYPE) << std::endl;
    }
  return 0;
}
