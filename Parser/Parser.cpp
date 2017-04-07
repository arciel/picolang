#include "Parser.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <utility>

Parser::Parser(Lexer &src)
{
    tksrc = &src;
}

Parser::~Parser()
{
}

int Parser::lbp(Token t)
{
    switch(t.token_type)
    {
        case TokenType::LIT_INTEGER:
        case TokenType::LIT_CHAR:
        case TokenType::LIT_STRING:
        case TokenType::LIT_CONST:
            //these are not infix operators.
            break;

        case TokenType::VAR:
            // var is a prefix token, whose lbp
            // isn't required.
            break;

        case TokenType::LAMBDA:
            // $ is a prefix token whose lbp
            // isn't required.
            break;

        case TokenType::MULT:
        case TokenType::DIV :
            return 70;
            break;

        case TokenType::PLUS:
        case TokenType::MINUS:
            return 60;
            break;

        case TokenType::MOD:
            return 50;
            break;

        case TokenType::CONS:
            return 30;
            break;

        case TokenType::ASSIGN:
            return 20;
            break;

        case TokenType::IS:
        case TokenType::HAS:
            return 25;
            break;

        case TokenType::RANGE:
            return 15;
            break;

        case TokenType::IF:
        case TokenType::THEN:
        case TokenType::ELSE:
        case TokenType::ENDIF:
            return 0;
            // stop when we reach any of these tokens.
            break;

        case TokenType::SEMICOLON:
        case TokenType::EOL:
        case TokenType::_EOF:
            return 0;
            break;

        case TokenType::IDENT:
            return 0;
            //we may have to process a function call.
            break;

        case TokenType::LBRKT:
        case TokenType::RBRKT:
            return 0;
            break;

        case TokenType::LCHEV:
        case TokenType::RCHEV:
            return 0;
            //the left of this may be sel-able, so
            //stop and give the left expression to 
            //select ( < )
            break;

        case TokenType::LPAREN:
        case TokenType::RPAREN:
            //stop when we reach ( or )
            return 0;
            break;

        case TokenType::COMMA:
        case TokenType::LEN:
            return 0;
            break;
        
        //default:
        //   std::cout << "Unknown token " << t << '\n';
        //    break;
    }

    std::cout << "Unexpected token " << t << '\n';
    return 0;
}

astnode_t Parser::test_nud(Token t)
{
    //std::cout << "[" << t.lexeme << "]";
    return std::make_unique<ASTLiteral>(t.lexeme, t.token_type);
}

astnode_t Parser::test_led(astnode_t left, Token t)
{
    auto op = std::make_unique<ASTArith>(t.token_type);
    op->set_left(std::move(left));
    op->set_right(std::move(parse_expr(lbp(t))));
    return std::move(op);
}

astnode_t Parser::parse_expr(int rbp)
{
    Token t = tksrc->peek();
    tksrc->get();

    astnode_t left = std::move(test_nud(t));

    while(rbp < lbp(tksrc->peek()))
    {
        t = tksrc->peek();
        tksrc->get();
        left = std::move(test_led(std::move(left), t));
    }

    return left;
}

int Parser::doit()
{
    astnode_t i = std::move(parse_expr(0));
    i->dump();
    return i->eval();
}
