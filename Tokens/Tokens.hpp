#pragma once

/*
    Tokens.hpp
    Defines the tokens emitted by the lexer.
*/

#include <string>
#include <unordered_map>

enum class TokenType
{
    NIL = 0,

    //Literals
    LIT_INTEGER, LIT_CHAR, LIT_STRING, LIT_CONST, // LIT_BOOL,

    //Groups
    LPAREN, RPAREN,  // ( )
    LBRACE, RBRACE,  // { }
    
    //Lists
    LBRKT, RBRKT,    // [ ]
    LCHEV, RCHEV,    // < >
    LAZY,            // ...
    RANGE,           // ..
    
    //Punctuation
    COMMA,           // ,
    LEN,             // | 
    
    //Infix.
    PLUS, MINUS, MULT, DIV, MOD, // + - * / mod
    ASSIGN,          // :=
    // Cons should be with the Lists group, but it is an infix operator
    CONS,         // ~
    
    //Sym
    VAR,             // var
//  CVAR            // const (future)    

    //Lambdas
    LAMBDA, LAMBDA_REF, LAMBDA_COPY, // $ -> =>
    
    //Identifier
    IDENT,
    
    //Conditionals
    IF, THEN, ELSE, ENDIF,  // if then else endif
    //BoolOps
    IS, HAS,         // is has

    //Endings
    SEMICOLON, EOL, _EOF,  // ; \n ^D

    COUNT
};



//define various categories of tokens
enum class TokenTypeOf
{
    NIL = 0,
    
    LITERAL,    // 123 'a' `hello` @t
    
    GROUP,      // () {}
    
    LIST,       // []  <> ... ..
    
    PUNCT,      // , |
    
    INFIX,      // + - * / mod ~ :=
    
    SYM,        // var const(future)
    
    LAMBDA,     // $ -> =>
    
    IDENT,      // varname
    
    COND,       // if then else endif
    
    BOOLOP,     // is has
    
    ENDING,     // ; \n ^D
    
    COUNT
};


//This shouldn't be here, but are required to
//be here as long as the extern global variables
//are here.
struct TokenTypeHash
{
    size_t operator()(TokenType const& t) const
    {
        return (int)t;
    }
};

struct TokenTypeOfHash
{
    size_t operator()(TokenTypeOf const& t) const
    {
        return (int)t;
    }
};

//This isn't good design.

extern std::unordered_map<TokenType, std::string, TokenTypeHash> TokenTypeLUT;
extern std::unordered_map<TokenTypeOf, std::string, TokenTypeOfHash> TokenTypeOfLUT;

extern std::unordered_map<std::string,TokenType> pico_kw;
extern std::unordered_map<TokenType,TokenTypeOf, TokenTypeHash> token_class;


struct Token
{
    TokenType token_type;
    TokenTypeOf token_type_of;
    std::string lexeme;
};

std::ostream& operator<<(std::ostream& out, Token tk);
