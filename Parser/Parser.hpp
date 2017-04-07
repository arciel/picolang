/*

    Parser for pico.
    The Parser reads in Tokens supplied by the lexer.
    Based on these tokens, the parser generates an AST like structure.

    The nodes of this tree implement the methods they represent. Once
    a tree representing source code has been generated, the root can
    simply be eval()'ed to run the program.

    The parser itself is an ad-hoc recursive descent parser,
    and makes use of Pratt-style operator precedence parsing.

    Some features of the language are detected and analyzed
    in places where they shouldn't be, and the design can be made cleaner.

    Still, not too bad.

    The grammar for pico can be found in the file Grammar2.ebnf

*/

#pragma once

#include "../Tokens/Tokens.hpp"
#include "../Lexer/Lexer.hpp"

#include <string>
#include <memory>

#include "../AST/ASTNode.hpp"
#include "AST.hpp"

class Parser
{
public:
    
    //Initialize the parser, passing in a token source.
    Parser(Lexer &src);
    
    //Return a pointer to the ASTManager object holding the generated AST.
    //ASTManager *get_ast();
    
    //Parse a top-level expression.
    astnode_t parse_expr(int rbp);
    
    int doit();
    
    //Free resources.
    ~Parser();

private:
    
    //Manages adding new nodes to the AST
    //ASTManager *ast_manager;
    
    //The token source
    Lexer *tksrc;
    
    //Return the left binding power of the given token
    int lbp(Token t);
    //Handle the case when t is a null denotation
    //i.e. t starts an expression
    astnode_t nud(Token t);
    //Handle the case when t is a left denotation.
    //i.e. t is in the middle of an expression.
    astnode_t led(Token t);
    
    //Dispatch when the token starts an expression.
    //This is the null-denotation of the token.
    
    astnode_t test_nud(Token t);
    //Dispatch when the token is infix.
    //This is the left-denotation of the token.
    
    astnode_t test_led(astnode_t l, Token t);
    //...
};
