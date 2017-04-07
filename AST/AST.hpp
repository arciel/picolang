#include "ASTRoot.hpp"  // holds top level expressions.

#include "ASTLiteral.hpp" // int char string list
#include "ASTIdent.hpp" // variable names
#include "ASTVar.hpp" // add names to the variable table
#include "ASTAssign.hpp" // :=

#include "ASTLambda.hpp" // make a lambda

#include "ASTArith.hpp" // + - * / mod
#include "ASTCons.hpp" // ~

#include "ASTIf.hpp" // if then else endif
#include "ASTBoolOp.hpp" // is has

#include "ASTSelector.hpp" // <...>
#include "ASTRange.hpp" // a..b
#include "ASTLen.hpp" // |list|

#include "ASTCall.hpp" // func(a)

#include "ASTSeq.hpp" // e1;e2
