#include <iostream>
#include <fstream>
#include "parser.h"
int yyparse();

int main(){
    
    std::filebuf fb;if (fb.open ("/home/monique/Documents/CompiladoresII/Parcial1/flexyBison_++/tests/test",std::ios::in)) {
    std::istream is(&fb);
    ExprLexer lex(is);
    Parser parser(lex);
    try{
        parser.parse();
    } catch(std::string& err){
        std::cerr << err;
    }
   
    return 0;
}