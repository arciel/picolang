
// The ASTNode base class.
// Each type of operand and operator in the language
// has a corresponding node class, each of which inherits
// this ASTNode class. 

// Every ASTNode subclass provides an eval() function
// which returns a picoVal object.

// To run the program, the eval() method is called for
// the root node of the AST, which in turn will call
// eval() on child nodes.

// I should probably seperate these, but I can't be
// bothered. Screw good practices!

#pragma once 
 
#include "../Interpreter/picoVal.hpp"

class ASTNode
{
public:
    //Execute this node.
    virtual picoVal eval() = 0;
    //Recursively dump the AST to STDOUT.
    virtual void dump() = 0;
    //Emit LLVM IR
    virtual int emit(int reg) = 0;
};

using astnode_t = std::unique_ptr<ASTNode>









