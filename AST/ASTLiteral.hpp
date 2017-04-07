#pragma once

// ASTLiteral corresponds to the nodes handling
// the value of literals encountered in source code.
// eval()'ing this will return the value of the literal.

#include "ASTNode.hpp"
#include "../Tokens/Tokens.hpp"

#include <string>


class ASTLiteral : public ASTNode
{
    TokenType t;
    /*picoVal*/ int val;
    
public:
    ASTLiteral(std::string src, TokenType _t);
    void dump() override;
    int eval() override;
};
