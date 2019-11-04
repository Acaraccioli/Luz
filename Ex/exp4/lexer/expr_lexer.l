%option noyywrap
%option reentrant

%{

#include "expr_lexer.h"
int counter =0;
#define YY_EXTRA_TYPE std::istream*
#define YY_DECL Token ExprLexer::_getNextToken(yyscan_t yyscanner)
#define YY_INPUT(buf,result,max_size)\
    do{\
        std::istream* in = yyget_extra(yyscanner);\
        in->read(buf,max_size);\
        result = in->gcount();\
    }while(0)

%}
%x linecomment
%x blockcomment

%%
[0-9]+"."[0-9]+ {text=yytext; return Token::Num; }
[0-9]+ {text=yytext; return Token::Num; }

[a-z_A-Z]+[a-z_A-Z0-9]+ {text=yytext; return Token::Id; }
<<EOF>> {return Token::Eof;}
"(" {text=yytext; return Token::OpenPar; }
")" {text=yytext; return Token::ClosePar; }
"-" {text=yytext; return Token::OpSub; }
"+" {text=yytext; return Token::OpAdd; }
"*" {text=yytext; return Token::OpMul; }
"/" {text=yytext; return Token::OpDiv; }
";" {text=yytext; return Token::Semicolon; }
"(*" {BEGIN(blockcomment);}
"--" {BEGIN(linecomment);}

<blockcomment>"*)" {BEGIN(INITIAL);}
<blockcomment>. {BEGIN(blockcomment);}

<blockcomment>"\n" {BEGIN(blockcomment);}
<linecomment>. {BEGIN(linecomment);}

<linecomment>"\n" {BEGIN(INITIAL);}




%%

ExprLexer::ExprLexer(std::istream &in):in(in) {
    yylex_init_extra(&in,&scanner);
}

ExprLexer::~ExprLexer() {
    yylex_destroy(scanner);
}
