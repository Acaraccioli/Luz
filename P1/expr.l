%option noyywrap
%option yylineno
%option reentrant

%{
#include <cstdio>
#include <iostream>
#include <sstream>
#include "expr_lexer.h"

#define YY_EXTRA_TYPE std::string
#define YY_DECL Token ExprLexer::_getNextToken(yyscan_t yyscanner)
int counter = 0;

#define YY_INPUT(buf, result, max_size)\
do{\
    std::istringstream ins;\
    ins.str(yyget_extra(yyscanner));\
    std::istream *in = &ins;\
    in->read(buf,max_size);\
    if(counter == 0){\
        counter++;\
        result = in->gcount();\
    }else{\
        result = 0;\
    }\
}while(0)

%}

%x BlockChain
%x LineChain

%%
[ ]
"0x"[0-9a-fA-F]+ {text = yytext;return Token::Hex;}
"0b"[0-1]+ {text = yytext; return Token::Binary;}
"0"[0-7]+ {text = yytext; return Token::Octal;}
[0-9]+ {text = yytext; return Token::Decimal;}
"#" { BEGIN(LineChain);}
\n { }
<INITIAL><<EOF>> {return Token::Eof;}
"(*" {BEGIN(BlockChain);}
. {std::string error = "error initial"; throw error;}

<LineChain>. { }
<LineChain>\n {BEGIN(INITIAL);}
<LineChain><<EOF>> {std::string error = "error line"; throw error;}

<BlockChain>"*)" {BEGIN(INITIAL);}
<BlockChain>. { }
<BlockChain>\n { }
<BlockChain><<EOF>> {std::string error = "error block"; throw error;}


%%

ExprLexer::ExprLexer(std::string in){
    yylex_init_extra(in, &scanner); 
}

ExprLexer::~ExprLexer() {
    yylex_destroy(scanner);
}

int ExprLexer::getLineNo() {
    return yyget_lineno(scanner);
}
