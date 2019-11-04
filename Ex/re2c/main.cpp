#include <iostream>
#include <fstream>
#include "expr_lexer.h"
int yyparse();

int main(){
    
    std::filebuf fb;
    if (fb.open ("/home/alejandro/Music/luz/Ex/ex2/test",std::ios::in)) {
        std::cout << "here" << std::endl;
        std::istream is(&fb);
        ExprLexer lex(is);
        while(lex.getNextToken() != Token::Eof);
        
    }
    return 0;
}
