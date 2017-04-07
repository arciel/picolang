#pragma once

#include "../Tokens/Tokens.hpp"
#include <istream>

/*
    The picolang lexer.
    This is matches the lexical units specified
    in `Grammar.ebnf`
*/

class Lexer
{
public:
    //Initiate a lexer, passing in a stream to tokenize from.
    //This will also read in a single token.
    Lexer(std::istream &src);
    //Return the last lex'd token, and read in a new one.
    Token get();
    //Peek at the last lex'd token.
    Token peek();
private:
    Token lex();
    std::istream *source;
    Token curtok;
};
