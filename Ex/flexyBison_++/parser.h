#include "expr_lexer.h"
#include "tokens.h"
class Parser {
public:
    Parser(ExprLexer& lex): lexer(lex){}

    int parse();
    void error(const char *msg);

    
private:
    ExprLexer& lexer;
    
};
