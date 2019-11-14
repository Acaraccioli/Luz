%option noyywrap
%option yylineno
%option reentrant


%{
#include <stdio.h>
#include <cstdio>
#include <sstream>
#include "expr_tokens.h"
#include "expr_lexer.h"

#define YY_EXTRA_TYPE std::istream*
#define YY_DECL int ExprLexer::_getNextToken(ExprLexer::semantic_type &yylval,yyscan_t yyscanner)
#define YY_INPUT(buf, result, max_size)\
do{\
    std::istream* in = yyget_extra(yyscanner);\
    in->read(buf,max_size);\
    result = in->gcount();\
}while(0)

%}
%x linecomment
%x blockcomment

%%


"/*" {BEGIN(blockcomment);}
"//" {BEGIN(linecomment);}

<blockcomment>"*/" {BEGIN(INITIAL);}
<blockcomment>. {BEGIN(blockcomment);}

<blockcomment>"\n" {BEGIN(blockcomment);}
<linecomment>. {BEGIN(linecomment);}

<linecomment>"\n" {BEGIN(INITIAL);}


"\n" { return makeToken(yytext, yyleng, token::EOL); }
<<EOF>> { return 0;}
"(" {
    return makeToken(yytext, yyleng, token::LEFTPAR);
}

")" {
    return makeToken(yytext, yyleng, token::RIGHTPAR);
}
"+" {
    return makeToken(yytext, yyleng, token::SUMA);
}

"-" {
    return makeToken(yytext, yyleng, token::RESTA);
}

"/" {
    return makeToken(yytext, yyleng, token::DIV);
}
"*" {
    return makeToken(yytext, yyleng, token::MULT);
}
";" {
    return makeToken(yytext, yyleng, token::SEMICOLON);
}

"<-" {
    return makeToken(yytext, yyleng, token::ASIGNACION);
}
"==" {
    return makeToken(yytext, yyleng, token::IGUALDAD);
}
"Escriba" {
    return makeToken(yytext, yyleng, token::ESCRIBA);
}
"Si" {
    return makeToken(yytext, yyleng, token::RW_SI);
}
"Entonces" {
    return makeToken(yytext, yyleng, token::RW_ENTONCES);
}
"Sino" {
    return makeToken(yytext, yyleng, token::RW_SINO);
}
"fin si" {
    return makeToken(yytext, yyleng, token::RW_FINSI); 
}
"fin mientras" {
    return makeToken(yytext, yyleng, token::RW_FINMIENTRAS);  
}
"Mientras" {
    return makeToken(yytext, yyleng, token::RW_MIENTRAS); 
}

"haga" {
    return makeToken(yytext, yyleng, token::RW_HAGA); 
}

"<>" {
    return makeToken(yytext, yyleng, token::NOIGUAL); 
}

"<" { 
    return makeToken(yytext, yyleng, token::MENORQUE); 
} 
">" { 
    return makeToken(yytext, yyleng, token::MAYORQUE); 
}
"<=" { 
    return makeToken(yytext, yyleng, token::MENORQUEOIGUAL
); }  
">=" { 
    return makeToken(yytext, yyleng, token::MAYORQUEOIGUAL); 
} 

"^" {
    return makeToken(yytext, yyleng, token::POWER); 
}
[0-9]+ {
    yylval.emplace<int>(std::strtol(yytext, nullptr,10));
    return makeToken(yytext, yyleng, token::NUMBER);
}

[a-z_A-Z]+[a-z_A-Z0-9]+ {
   yylval.emplace<std::string>(yytext, yyleng);
    return makeToken(yytext, yyleng, token::IDENT);
}

%%

ExprLexer::ExprLexer(std::istream &in) : in(in){
    yylex_init_extra(&in, &scanner); 
}


int ExprLexer::getLineNo() {
    return yyget_lineno(scanner);
}