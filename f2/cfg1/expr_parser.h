#include "expr_lexer.h"

class Parser {
public:
    Parser(ExprLexer& lex, YYNODESTATE sta, ASTNode * stmt): lexer(lex), state(sta),stmtList(stmt){}

    void parser();
    void error(const char *msg);

    
private:
    ExprLexer& lexer;
    YYNODESTATE state;
    ASTNode * stmtList;
    std::unordered_map<std::string,int> idents;
};