#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "expr_lexer.h"
#include "expr_parser.h"
int yyparse();

int main(int argc, char **argv){

    YYNODESTATE state;

    ASTNode * stmtList;
    std::filebuf fb;
    if (fb.open (argv[1],std::ios::in)) {
        std::unordered_map<std::string,int> idents;
        std::istream is(&fb); 
        ExprLexer lex(is);
        Expr::Parser pars(lex,state,stmtList);
        pars.parse();
        stmtList->eval(idents);
        fb.close();
    }
    return 0;
}