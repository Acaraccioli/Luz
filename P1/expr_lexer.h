#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

using yyscan_t = void*;

enum class Token{
    Hex,
    Octal,
    Binary,
    Decimal,
    Eof
};

class ExprLexer {
public:
    ExprLexer(std::string in);
    ~ExprLexer();
    Token getNextToken() { return _getNextToken(scanner); }
    std::string getText() { return text; }
    int getLineNo();

private:
    /* Flex will generate this function */
    Token _getNextToken(yyscan_t yyscanner);

private:
    std::string text;
    yyscan_t scanner;
};
#endif
