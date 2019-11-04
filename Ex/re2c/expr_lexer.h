#include <stdio.h>
#include <string.h>
#include <iostream>

#define SIZE 1024

enum Token { 
    Error,
    Eof,
    OpAdd,
    OpSub,
    OpMul,
    OpDiv,
    OpenPar,
    ClosePar,
    Semicolon,
    Number,
    Ident,
    If,
    Then,
    Else,
    EndIf,
    Print,
    Assign,
    While,
    Do,
    EndWhile
};

class ExprLexer {
public:

    ExprLexer(std::istream &in) : ctx(in), lineno(1){}
    ~ExprLexer(){}
    Token getNextToken();

    enum class FillStatus{
        Ok,
        Error,
        Eof
    };

    struct Context{
        char * buf;
        char * tok;
        char * lim;
        char * cur;
        bool eof;
        std::istream &in;
        Context(std::istream &in);
        ~Context(){ delete [] buf; }

        FillStatus fill(size_t need);
        std::string tokenText(){ return std::string(tok,cur-tok); }
    };

    Token makeToken(Token tk){ 
        text = ctx.tokenText();
        return tk;
    }

    Token tkEof(){
        text = "<<EOF>>";
        return Token::Eof;
    }

    Token tkError(){
        text = "Error";
        return Token::Error;
    }

    int lineno;
    Context ctx;
    std::string text;
    int state;

};

