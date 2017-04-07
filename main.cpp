#include <iostream>
#include <fstream>
#include <functional>

#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"

int main(int argc, char *argv[])
{

    std::ifstream fin;

    if(argc > 1)
        fin.open(argv[1]);

    Lexer lex { argc > 1 ? fin : std::cin };
    Parser parse { lex };
    //while(lex.peek().token_type != TokenType::_EOF)
    //{
    //    std::cout << lex.peek();
    //    lex.get();
    //}
    
    std::cout << '\n' << parse.doit();

    //parse.parse();
    //parse.get_ast().dump();

    return 0;
}
