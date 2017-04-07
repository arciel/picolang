#include "Tokens.hpp"

#include <iostream>
#include <unordered_map>

//TODO : Do this with pre-processor hacks!

std::unordered_map<TokenType, std::string, TokenTypeHash> TokenTypeLUT
{
    {TokenType::NIL,"NIL"},
    
    {TokenType::LIT_INTEGER,"INTEGER"},
    {TokenType::LIT_CHAR, "CHAR"},
    {TokenType::LIT_STRING, "STRING" },
    {TokenType::LIT_CONST, "CONSTANT"},
    
    {TokenType::LPAREN, "LPAREN" },
    {TokenType::RPAREN,"RPAREN"},
    {TokenType::LBRACE, "LBRACE" },
    {TokenType::RBRACE,"RBRACE"},
    
    {TokenType::LBRKT, "LBRKT" },
    {TokenType::RBRKT, "RBRKT"},
    {TokenType::LCHEV, "LCHEV" },
    {TokenType::RCHEV, "RCHEV"},
    {TokenType::LAZY,  "LAZY" },
    {TokenType::RANGE, "RANGE"},
    
    {TokenType::COMMA, "COMMA"},
    {TokenType::LEN, "LEN"},
    
    {TokenType::PLUS, "PLUS" },
    {TokenType::MINUS, "MINUS" },
    {TokenType::MULT, "MULT" },
    {TokenType::DIV, "DIV" },
    {TokenType::MOD,"MOD"},
    {TokenType::ASSIGN,"ASSIGN"},
    {TokenType::CONS, "CONS"},
    
    
    {TokenType::VAR,"VAR"},
//  {TokenType::CVAR,"CVAR"},
    
    {TokenType::LAMBDA, "LAMBDA"},
    {TokenType::LAMBDA_REF, "BYREF"},
    {TokenType::LAMBDA_COPY,"BYCOPY"},
    
    {TokenType::IDENT,"IDENT"},
    
    {TokenType::IF, "IF" },
    {TokenType::THEN, "THEN" },
    {TokenType::ELSE,"ELSE"},
    {TokenType::ENDIF,"ENDIF"},
    
    {TokenType::IS, "IS" },
    {TokenType::HAS,"HAS"},
    
    {TokenType::SEMICOLON, "SEPRTR"},
    {TokenType::EOL,"EOL"},
    {TokenType::_EOF,"EOF"}
};

std::unordered_map<TokenTypeOf, std::string, TokenTypeOfHash> TokenTypeOfLUT
{
    {TokenTypeOf::NIL,"NIL"},
    {TokenTypeOf::LITERAL,"Literal"},
    {TokenTypeOf::GROUP,"Group"},
    {TokenTypeOf::LIST,"List"},
    {TokenTypeOf::PUNCT,"Punct."},
    {TokenTypeOf::INFIX,"Infix"},
    {TokenTypeOf::SYM,"Symbol"},
    {TokenTypeOf::LAMBDA,"Lambda"},
    {TokenTypeOf::IDENT,"Identifier"},
    {TokenTypeOf::COND,"Conditional"},
    {TokenTypeOf::BOOLOP,"Boolean"},
    {TokenTypeOf::ENDING,"End"}
};

std::unordered_map<std::string,TokenType> pico_kw
{
    {"var", TokenType::VAR},
//  {"const", TokenType::CVAR},  
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE},
    {"endif", TokenType::ENDIF},
    
    {"is", TokenType::IS},
    {"has", TokenType::HAS},
    
    {"mod", TokenType::MOD}
    
};

std::unordered_map<TokenType,TokenTypeOf,TokenTypeHash> token_class
{
    {TokenType::NIL, TokenTypeOf::NIL},
    
    {TokenType::LIT_INTEGER, TokenTypeOf::LITERAL},
    {TokenType::LIT_CHAR,TokenTypeOf::LITERAL},
    {TokenType::LIT_STRING,TokenTypeOf::LITERAL},
    {TokenType::LIT_CONST,TokenTypeOf::LITERAL},
    
    {TokenType::LPAREN,TokenTypeOf::GROUP},
    {TokenType::RPAREN,TokenTypeOf::GROUP},
    {TokenType::LBRACE,TokenTypeOf::GROUP},
    {TokenType::RBRACE,TokenTypeOf::GROUP},
    
    {TokenType::LBRKT,TokenTypeOf::LIST},
    {TokenType::RBRKT,TokenTypeOf::LIST},
    {TokenType::LCHEV,TokenTypeOf::LIST},
    {TokenType::RCHEV,TokenTypeOf::LIST},
    {TokenType::LAZY,TokenTypeOf::LIST},
    {TokenType::RANGE,TokenTypeOf::LIST},
    
    {TokenType::LEN,TokenTypeOf::PUNCT},
    {TokenType::COMMA, TokenTypeOf::PUNCT},
    
    {TokenType::PLUS,TokenTypeOf::INFIX},
    {TokenType::MINUS,TokenTypeOf::INFIX},
    {TokenType::MULT,TokenTypeOf::INFIX},
    {TokenType::DIV,TokenTypeOf::INFIX},
    {TokenType::MOD,TokenTypeOf::INFIX},
    {TokenType::ASSIGN,TokenTypeOf::INFIX},
    {TokenType::CONS,TokenTypeOf::INFIX},
    
    {TokenType::VAR,TokenTypeOf::SYM},
    
    {TokenType::LAMBDA,TokenTypeOf::LAMBDA},
    {TokenType::LAMBDA_REF,TokenTypeOf::LAMBDA},
    {TokenType::LAMBDA_COPY,TokenTypeOf::LAMBDA},
    
    {TokenType::IDENT,TokenTypeOf::IDENT},
    
    {TokenType::IF,TokenTypeOf::COND},
    {TokenType::THEN,TokenTypeOf::COND},
    {TokenType::ELSE,TokenTypeOf::COND},
    {TokenType::ENDIF,TokenTypeOf::COND},
    
    {TokenType::IS,TokenTypeOf::BOOLOP},
    {TokenType::HAS,TokenTypeOf::BOOLOP},
     
    {TokenType::EOL, TokenTypeOf::ENDING},
    {TokenType::SEMICOLON, TokenTypeOf::ENDING},
    {TokenType::_EOF, TokenTypeOf::ENDING}
};

std::ostream& operator<<(std::ostream& out, Token tk)
{
    return out << "Token = (" <<
                    TokenTypeOfLUT.at(tk.token_type_of) << ", " << // <<
                    TokenTypeLUT.at(tk.token_type) << ", " << "\"" <<
                    tk.lexeme << "\")\n";
}
