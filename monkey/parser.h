#include "expr_lexer.h"
#include "expr_tokens.h"
#include <unordered_map>
#include <map>
#include <vector>
class Parser {
public:
   // Parser(ExprLexer& lex): lexer(lex){}
    //Parser(ExprLexer& lex, std::unordered_map<std::string, int> vars,  std::vector<int> values): lexer(lex){}
    //void parser(ExprLexer *lex, std::unordered_map<std::string, int> vars,  std::vector<int> values);
     Parser(ExprLexer& lexer, YYNODESTATE state): lexer(lexer), state(state){}
    void parser();
    void error(const char *msg);

   

private:
    ExprLexer& lexer;
    YYNODESTATE state;

    
};
