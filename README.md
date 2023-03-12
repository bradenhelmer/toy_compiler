# toy_compiler Project
Implementation of a compiler for a C style language using LLVM. I used this [article](https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/) as a base but the LLVM section is vastly outdated. Additionally, I opted to write a native lexer and parser rather than using Flex and Bison. 
## Project Goals
I would like to extend/modify this project in a few areas:
- Support control and iterative statements.
- Support string, char, array, and struct types.
