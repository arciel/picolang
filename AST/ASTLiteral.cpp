 
#include "ASTLiteral.hpp"

#include <iostream>

ASTLiteral::ASTLiteral(std::string src, TokenType _t)
{
    t = _t;
    val = std::stoi(src);
}

void ASTLiteral::dump()
{
    std::cout << "(" << val << ")";
}

int ASTLiteral::eval()
{
    return val;
}
