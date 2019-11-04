#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "tokens.h"

using yyscan_t = void*;

class ExprLexer{
public: 
    using semantic_type = Expr::Parser::semantic_type;
    using token = Expr::Parser::token;

    ExprLexer(std::istream &in);

    int getNextToken(semantic_type *yylval){
        return _getNextToken(*yylval,scanner);
    }
    std::string getText() { return text; }
    int getLineNo();
private:

    int makeToken(const char * txt, int len, int tk){
        std::string tt(txt,len);
        text = std::move(tt);
        return tk;
    }
    int _getNextToken(semantic_type &yylval,yyscan_t yyscanner);
    
    std::istream &in;
    std::string text;
    yyscan_t scanner;
};