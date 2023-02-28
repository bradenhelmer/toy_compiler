#include <iostream>
#include "tokens.h"
#include "lexer.h"

int main(int argc, char **argv) {

    const char *test = "This is a test program";
    
    Lexer *lex = new Lexer(test);
    Token *tok = lex->lexToken();
    if (tok->getType() == tokdef::ID) {
        std::cout << tok->getPtrVal() << std::endl;
        return 0;
    }
    return 1;
}
