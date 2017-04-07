 
#include "ASTArith.hpp"
#include "../Tokens/Tokens.hpp"

#include <iostream>
#include <utility>


ASTArith::ASTArith(TokenType _t) : t{_t} {}

void ASTArith::dump()
{
    std::cout << "(";
    switch(t)
    {
        case TokenType::PLUS : std::cout << "+";break;
        case TokenType::MINUS : std::cout << "-";break;
        case TokenType::MULT : std::cout << "*";break;
        case TokenType::DIV  : std::cout << "/";break;
        case TokenType::MOD : std::cout << "mod";break;
    }
    
    std::cout << '\n';
    
    std::cout << "  "; left->dump();
    std::cout << '\n';
    std::cout << "  "; right->dump();
    std::cout << ")";
}

/*picoVal*/int ASTArith::eval()
{
    int r;
    int a = left->eval();
    int b = right->eval();
    switch(t)
    {
        case TokenType::PLUS : r = a + b;break;
        case TokenType::MINUS : r = a - b;break;
        case TokenType::MULT : r = a * b;break;
        case TokenType::DIV  : r = a / b;break;
        case TokenType::MOD : r = a % b;break;
    }
    
    return r;
}
    
void ASTArith::set_left(std::unique_ptr<ASTNode> l)
{
    left = std::move(l);
}
    
void ASTArith::set_right(std::unique_ptr<ASTNode> r)
{
    right = std::move(r);
}    
    
    
    
    
    
