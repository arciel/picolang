#pragma once


// ASTArith corresponds to the nodes handling
// the mathematical operations for + - * / and `mod`

#include <memory>

#include "../Tokens/Tokens.hpp"
#include "ASTNode.hpp"


class ASTArith : public ASTNode
{
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    TokenType t;
public :
    
    ASTArith(TokenType _t);
    
    void set_left(std::unique_ptr<ASTNode> l);
    void set_right(std::unique_ptr<ASTNode> r);
    
    void dump() override;
    /*picoVal*/int eval() override;
};

