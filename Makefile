CC=g++
CCFLAGS=-c -g -Wall -Werror -Wpedantic -std=c++14
EXECUTABLE=pico

tokens:
	$(CC) $(CCFLAGS) ./Tokens/Tokens.cpp

lexer:
	cd Lexer/
	$(CC) $(CCFLAGS) ./Lexer/Lexer.cpp

parser:
	cd Parser/
	$(CC) $(CCFLAGS) ./Parser.cpp

ast:
	cd AST/
	$(CC) $(CCFLAGS) ./AST.cpp

interpreter:
	cd Interpreter/
	$(CC) $(CCFLAGS) ./Interpreter.cpp

driver:
	$(CC) $(CCFLAGS) ./main.cpp

all: tokens lexer driver
	$(CC) *.o -o $(EXECUTABLE)

clean:
	rm *.o
