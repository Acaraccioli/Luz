#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

#include <istream>

using std::istream;

using yyscan_t = void*;

enum class Token {
    Num,
    OpAdd,
    OpSub,
    Id,
    Eof,
    OpenPar,
    ClosePar,
    Semicolon
};

class ExprLexer {
public:
    ExprLexer(istream& in);
    ~ExprLexer();

    
    Token getNextToken() { return _getNextToken(scanner); }
    std::string getText() { return text; }

private:
    /* Flex will generate this function */
    Token _getNextToken(yyscan_t yyscanner);

private:
    std::istream &in;
    std::string text;
    yyscan_t scanner;

};
#endif
