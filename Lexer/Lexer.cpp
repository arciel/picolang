// // 
#include "Lexer.hpp"
#include "../Tokens/Tokens.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

#ifndef EOF
#define EOF -1
#endif // EOF

Lexer::Lexer(std::istream &src)
{
    this->source = &src;
    this->curtok = {TokenType::NIL,TokenTypeOf::NIL,""};
    this->curtok = this->lex();
}

Token Lexer::get()
{
    Token r = this->curtok;
    this->curtok = this->lex();
    return r;
}

Token Lexer::peek()
{
    return this->curtok;
}

Token Lexer::lex()
{

  Token ret = {TokenType::NIL, TokenTypeOf::NIL, ""};
  std::string lexeme = "";

lex_begin:

    char c = this->source->get();
    this->source->putback(c);

    if(isspace(c))
      {
        //TODO : Deal with \t spaces.
        this->source->ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        goto lex_begin;
      }

    if(c == EOF)   goto lex_eof;
    if(c == '#')   goto lex_comment; //ignore everything from # to end of the line
    if(c == '\0')  goto lex_eol; // this doesn't seem to work?  :( :( D:
    if(c == '\n')  goto lex_eol; // this doesn't seem to work?! WWWWWHHHHHYYYYYYYYYY?

    if(isalpha(c)) goto lex_kw_ident; // try to lex an ident or a keyword

    if(isdigit(c)) goto lex_lit_posnumber; //try to lex a positive number
    if(c == '\'')  goto lex_lit_char; //try to lex a character
    if(c == '`')   goto lex_lit_string; //try to lex a string literal
    if(c == '@')   goto lex_lit_const;//try to lex a constant

    if(ispunct(c)) goto lex_further; //try to lex symbols and operators


    goto invalid_lex;

lex_comment:
    {
        this->source->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto lex_begin;
    }

lex_kw_ident:
    {
      char c = this->source->get();
      while(isalnum(c))
      {
        lexeme += c;
        c = this->source->get();
      }
      if(pico_kw.count(lexeme) == 0)
      {
        ret.token_type = TokenType::IDENT;
        ret.token_type_of = token_class[ret.token_type];
      }
      else
      {
        ret.token_type = pico_kw[lexeme];
        ret.token_type_of = token_class[ret.token_type];
      }
      this->source->putback(c);
      ret.lexeme = lexeme;
      return ret;
    }

lex_lit_posnumber:
    {
      char c = this->source->get();
      while(isdigit(c))
      {
        lexeme += c;
        c = this->source->get();
      }
      this->source->putback(c);
      ret.token_type = TokenType::LIT_INTEGER;
      ret.token_type_of = token_class[ret.token_type];
      ret.lexeme = lexeme;
      return ret;
    }

lex_lit_string:
    {
      this->source->get(); //consume opening backtick.
      for(char c = this->source->get();c!='`'; c = this->source->get())
      {
        lexeme += c;
      }
      //this messes up when encountering something like
      // `helloworld`123 and incorrectly lexes it as
      // two seperate tokens.
      ret.token_type = TokenType::LIT_STRING;
      ret.token_type_of = token_class[ret.token_type];
      ret.lexeme = lexeme;
      return ret;
    }

lex_lit_char:
    {
        this->source->get(); //consume opening quote
        ret.token_type=TokenType::LIT_CHAR;
        ret.token_type_of = token_class[ret.token_type];
        ret.lexeme = this->source->get();
        if(this->source->get() != '\'')
            std::cout << "expected closing single-quote!\n";
        return ret;
    }

lex_lit_const:
    {
        this->source->get(); //consume @ sign
        char c = this->source->get();
        while(isalnum(c))
        {
            lexeme += c;
            c = this->source->get();
        }
        this->source->putback(c);
        ret.token_type = TokenType::LIT_CONST;
        ret.token_type_of = token_class[ret.token_type];
        ret.lexeme = lexeme;
        return ret;        
    }
    
    
lex_further:
    {
      c = this->source->get();
      switch(c)
      {
        case '|': ret.token_type=TokenType::LEN;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;

        case '~': ret.token_type=TokenType::CONS;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;

        case ',': ret.token_type=TokenType::COMMA;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;

        case ';': ret.token_type=TokenType::SEMICOLON;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;

        case '$': ret.token_type=TokenType::LAMBDA;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;

        case '+': ret.token_type=TokenType::PLUS;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        //case '-': ret.token_type=TokenType::MINUS;
        //         ret.token_type_of=token_class[ret.token_type];
        //         ret.lexeme += c;
        //         return ret; break
        case '*': ret.token_type=TokenType::MULT;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '/': ret.token_type=TokenType::DIV;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '(': ret.token_type=TokenType::LPAREN;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case ')': ret.token_type=TokenType::RPAREN;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '[': ret.token_type=TokenType::LBRKT;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case ']': ret.token_type=TokenType::RBRKT;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '{': ret.token_type=TokenType::LBRACE;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '}': ret.token_type=TokenType::RBRACE;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '<': ret.token_type=TokenType::LCHEV;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case '>': ret.token_type=TokenType::RCHEV;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += c;
                  return ret; break;
        case ':':  if(this->source->get() == '=')
                  {
                  ret.token_type=TokenType::ASSIGN;
                  ret.token_type_of=token_class[ret.token_type];
                  ret.lexeme += ":=";
                  return ret;
                  }
                  else {std::cout << "Stray `:` in program.\n"; return ret;}
                  break;
        case '.':{
                char c2 = this->source->get();
                char c3 = this->source->get();
                if(c2 == '.')
                {
                    if(c3 == '.')
                    {
                        ret.token_type=TokenType::LAZY;
                        ret.token_type_of=token_class[ret.token_type];
                        ret.lexeme += "...";
                        return ret;
                    }
                    else
                    {
                        this->source->putback(c3);
                        ret.token_type=TokenType::RANGE;
                        ret.token_type_of=token_class[ret.token_type];
                        ret.lexeme += "..";
                        return ret;
                    }
                }
                else
                {
                    this->source->putback(c3);
                    this->source->putback(c2);
                    std::cout << "Stray `.` in program \n";
                    return ret;
                }
                return ret;
                }; break;
        case '-':{
                  char c2 = this->source->get();
                  if(c2 == '>')
                  {
                    ret.token_type=TokenType::LAMBDA_COPY;
                    ret.token_type_of=token_class[ret.token_type];
                    ret.lexeme += "->";
                  }
                  else
                  {
                    this->source->putback(c2);
                    ret.token_type=TokenType::MINUS;
                    ret.token_type_of=token_class[ret.token_type];
                    ret.lexeme += "-";
                  }
                  return ret;
                  }; break;
        case '=': {
                  char c2 = this->source->get();
                  if(c2 == '>')
                  {
                    ret.token_type=TokenType::LAMBDA_REF;
                    ret.token_type_of=token_class[ret.token_type];
                    ret.lexeme += "=>";
                  }
                  else
                  {///TODO ERROR GEN
                    this->source->putback(c2);
                    std::cout << "Stray `=` in program. Did you mean `:=`?\n";
                  }
                  return ret;
                 }; break;
        default : std::cout << "Unknown " << c << " in program.\n";
                  return ret; break;
     }
  }
lex_eol:
    {
      ret.token_type=TokenType::EOL;
      ret.token_type_of=token_class[ret.token_type];
      ret.lexeme += "\\n";
      return ret;
    }
lex_eof:
    {
      ret.token_type = TokenType::_EOF;
      ret.token_type_of = token_class[ret.token_type];
      return ret;
    }


invalid_lex: return ret;
}
