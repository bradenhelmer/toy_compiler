// lexer.h
// ~~~~~~~
// This file defines the lexer interface
#include "tokens.h"

class Lexer {

const char *srcBuffer;
Token curToken;

public:
    Lexer(const char *srcBuffer) : srcBuffer(srcBuffer) {}
    void skipWhiteSpace();
    int lexToken();
    void lexStringLiteral();
    void lexNumericLiteral();

};
