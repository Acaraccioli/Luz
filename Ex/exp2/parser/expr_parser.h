#ifndef _EXPR_PARSER_H
#define _EXPR_PARSER_H

#include <vector>
#include "expr_lexer.h"
#include "build/expr_tokens.h"

class ExprParser {
public:
    ExprParser(ExprLexer& lex): lexer(lex){}
    ~ExprParser(){};

    int parse();
    void yyerror(const char *msg);

    int getExprCount() {
        return map.size();
    }
    
    int getExprValue(int index) {
        return map[index];
    }
    
private:
    std::vector<double> map;
    ExprLexer& lexer;

};

#endif
