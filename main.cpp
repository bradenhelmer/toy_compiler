#include <iostream>
#include "codegen.h"
#include "node.h"

extern int yyparse();
extern NBlock* programBlock;

int main(int argc, char **argv) {
    std::cout << "TEST" << std::endl;
    yyparse();
    std::cout << programBlock << std::endl;

    CodeGenContext context;
    context.generateCode(*programBlock);
    return 0;
}
