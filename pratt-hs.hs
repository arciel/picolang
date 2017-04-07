{-# LANGUAGE InstanceSigs #-}
{-# LANGUAGE LambdaCase #-}

import Control.Monad.State

data Token = Num Int | Ident String | OpAdd | OpSub | OpMul | OpDiv | OpAssgn | LParen | RParen | EOF deriving (Eq, Show)
data Expr = Lit Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr | Brack Expr | Assgn String Expr deriving (Eq, Show)

-- The Lexer (poor man's)
tokenize :: String -> [Token]
tokenize xs = map (\x -> case x of 
                            "+" -> OpAdd
                            "*" -> OpMul
                            "-" -> OpSub
                            "/" -> OpDiv
                            "(" -> LParen
                            ")" -> RParen
                            "=" -> OpAssgn
                            _ -> Num $ read x)
                        (words xs) ++ [EOF]
-- The Parser

lbp :: Token -> Int
led :: Expr -> State [Token] Expr
nud :: State [Token] Expr
express :: Int -> State [Token] Expr

lbp OpAdd = 10
lbp OpSub = 10
lbp OpMul = 20
lbp OpDiv = 20
lbp LParen = 2
lbp RParen = 0
lbp EOF      = 0
lbp (Num _ ) = 1

led e1 = do
    (t:ts) <- get
    put ts
    e2 <- express (lbp t)
    -- TODO : get rid of repeated `e1`, `e2`
    return $ case t of
             OpAdd -> Add e1 e2
             OpSub -> Sub e1 e2
             OpMul -> Mul e1 e2
             OpDiv -> Div e1 e2
             EOF -> error "LED got EOF"

nud = do
        (t:ts) <- get
        put ts
        case t of
            (Num i) -> return $ Lit i
            LParen -> do { e <- express (lbp t); (t:ts) <- get; put ts; return $ Brack e }
            RParen -> error "WTF"
            EOF -> error "NUD got EOF"

express rbp = do
    left <- nud
    e <-  collect rbp left
    return e

collect :: Int -> Expr -> State [Token] Expr
collect rbp e = do
    (t:ts) <- get
    if (lbp t > rbp)
    then do
        e' <- led e
        collect rbp e'
    else return e



-- The Evaluator

evalExpr :: Expr -> Rational
evalExpr (Lit i) = toRational i
evalExpr (Add e1 e2) = evalExpr e1 + evalExpr e2
evalExpr (Sub e1 e2) = evalExpr e1 - evalExpr e2
evalExpr (Mul e1 e2) = evalExpr e1 * evalExpr e2
evalExpr (Div e1 e2) = evalExpr e1 / evalExpr e2
evalExpr (Brack e) = evalExpr e

test :: String -> Float
test xs = fromRational (evalExpr $ evalState (express 0) (tokenize xs))
