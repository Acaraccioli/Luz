#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

#include <iostream>
#include <fstream>
#include <string>

enum class Token{
    OpSub,
    OpAdd,
    OpMul,
    OpDiv,
    Num,
    Id,
    Eof,
    OpenPar,
    ClosePar,
    Semicolon
};

using yyscan_t = void*;

class ExprLexer {
public:
    ExprLexer(std::istream &in);
    ~ExprLexer();

    Token getNextToken() { return _getNextToken(scanner); }
    std::string getText() { return text; }

private:
    Token _getNextToken(yyscan_t yyscanner);
    std::istream &in;
    std::string text;
    yyscan_t scanner;
};
#endif
