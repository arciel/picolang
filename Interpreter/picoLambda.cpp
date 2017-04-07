// Each picoLambda stores a tiny AST,
// representing the code for the lambda.
// When picoLambdas are called, the AST root
// is eval()'d like in the regular case, but
// the params passed to the lambda are added to the 
// internal symbol table so that they appear to be 
// regular variables.

// For ref-lambdas... I'm not quite sure. Perhaps pointers
// instead of ident names? Or maybe the call() changes the 
// passed params in the global symbol table?


