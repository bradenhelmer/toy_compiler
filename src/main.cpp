#include <iostream>
#include "codegen.h"
#include "node.h"

extern int yyparse();
extern NBlock* programBlock;

int main(int argc, char **argv) {

    yyparse();
    std::cout << "TEST" << std::endl;
    return 0;

    CodeGenContext context;
    context.generateCode(*programBlock);
    return 0;
}
