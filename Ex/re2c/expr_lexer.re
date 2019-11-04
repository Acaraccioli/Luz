#include <istream>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "expr_lexer.h"

/*!max:re2c*/

Token ExprLexer::getNextToken(){
    #define YYFILL(n) do { \
        FillStatus st = ctx.fill(n); \
        if(st == FillStatus::Eof){ \
            return tkEof(); \
        } else if(st == FillStatus::Error){ \
            return tkError(); \
        } else { \
            break; \
        } \
    } while(0); \

    while(1){
        ctx.tok = ctx.cur;
        char *YYMARKER;

        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYLIMIT = ctx.lim;
            re2c:define:YYCURSOR = ctx.cur;
            re2c:define:YYFILL:naked = 0;
            END = "\x00";
            NUMBER = [0-9]*;
            IDENT = [_a-zA-Z][0-9a-zA-Z]*;
            WSP = [ \t]*;
        */
            

            if(state == 0) { goto input;}
            else if(state == 1){ goto lineComment;}
            else if(state == 2){ goto blockComment;}
        input:
         /*!re2c
            "/*"  {state = 2; continue;}
            "//"   {state = 1; continue;}
            * { return tkError(); }
            WSP { continue ; }
            END { return tkEof(); }
            "+" { std::cout << "SUMA" << std::endl; return makeToken(Token::OpAdd); }
            "-" { std::cout << "RES" << std::endl;return makeToken(Token::OpSub); }
            "*" { std::cout << "MUL" << std::endl;return makeToken(Token::OpMul); }
            "/" { std::cout << "DIV" << std::endl;return makeToken(Token::OpDiv); }
            "(" { std::cout << "OPENPAR" << std::endl;return makeToken(Token::OpenPar); }
            ")" { std::cout << "CLOSEPAR" << std::endl;return makeToken(Token::ClosePar); }
            ";" { return makeToken(Token::Semicolon); }
            "Si" { std::cout << "IF" << std::endl;return makeToken(Token::If); }
            "entonces" { std::cout << "THEN" << std::endl;return makeToken(Token::Then); }
            "sino" { std::cout << "ELSE" << std::endl;return makeToken(Token::Else); }
            "fin si" {std::cout << "ENDIF" << std::endl; return makeToken(Token::EndIf); }
            "Mientras" { std::cout << "WHILE" << std::endl;return makeToken(Token::While); }
            "haga" { std::cout << "DO" << std::endl;return makeToken(Token::Do); }
            "fin mientras" { std::cout << "ENDWHILE" << std::endl;return makeToken(Token::EndWhile); }
            "<-" { std::cout << "ASSIGN" << std::endl;return makeToken(Token::Assign); }
            "Escriba" { std::cout << "PRINT" << std::endl;return makeToken(Token::Print); }
            NUMBER { std::cout << "NUM" << std::endl;return makeToken(Token::Number); }
            IDENT { std::cout << "ID" << std::endl; return makeToken(Token::Ident); }
            
        */

     lineComment:
        /*!re2c
            "\n" {lineno++; state = 0; continue;}
            * {state = 1; continue;}
        */
        blockComment:
        /*!re2c
            "*\/" {state = 0; continue;}
            [\n]  {lineno++; state = 2; continue;}
            * {state = 2; continue;}
            
        */
        
    }
}

ExprLexer::Context::Context(std::istream &in): in(in){
    buf = new char[SIZE+YYMAXFILL];
    lim = buf+SIZE;
    cur = lim;
    tok = lim;
    eof = false;
}

ExprLexer::FillStatus ExprLexer::Context::fill(size_t need){
    if (eof) {
        return FillStatus::Eof;
    }
    const size_t free = tok - buf;
    if (free < need) {
        return FillStatus::Error;
    }

    memmove(buf, tok, lim - tok);
    lim -= free;
    cur -= free;
    tok -= free;
    in.read(lim,free);
    lim += in.gcount();
    printf("LIM: %s\n", lim);
    //std::cout << "LIM: "<< lim << std::endl;
    if (lim < buf + SIZE) {
        eof = true;
        memset(lim, 0, YYMAXFILL);
        lim += YYMAXFILL;
    }
    return FillStatus::Ok;
}




