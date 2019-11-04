%option noyywrap
%option yylineno
%option reentrant


%x comment
%{
#include <stdio.h>
#include <cstdio>
#include <sstream>
#include "tokens.h"
#define YY_EXTRA_TYPE std::istream*
#define YY_DECL int ExprLexer::_getNextToken(ExprLexer::semantic_type &yylval,yyscan_t yyscanner)
#define YY_INPUT(buf, result, max_size)\
do{\
    std::istream* in = yyget_extra(yyscanner);\
    in->read(buf,max_size);\
    result = in->gcount();\
}while(0)

%}

%%

"print" {
    //printf("%s TK_PRINT\n", yytext);
    return TK_PRINT; 
}

[0-9]+ {
    yylval.emplace<int>(std::strtol(yytext, nullptr,10));
    return makeToken(yytext, yyleng, TK_NUMBER);
    //printf("%s NUMBER\n", yytext);
    return TK_NUMBER; 
}

[a-zA-Z_][0-9a-zA-Z_]* {
    yyval.emplace<std::string>(yytext, yyleng);
    return makeToken(yytext, yyleng, TK_IDENT);
    //printf("%s IDENTIFIER\n", yytext);
    return TK_IDENT; 
}

"=" {
    //printf("%s TK_ASSIGN\n", yytext);
    return makeToken(yytext, yyleng, TK_ASSIGN);
}

"(" {
    //printf("%s TK_LEFTPAR\n", yytext);
    return makeToken(yytext, yyleng, TK_LEFTPAR);
}

")" {
    //printf("%s TK_RIGHTPAR\n", yytext);
    return makeToken(yytext, yyleng, TK_RIGHTPAR);
}

"+"|"-"|"*"|"/" {
    if(yytext[0] == '+'){
        //printf("%s TK_SUMA\n", yytext);
        return makeToken(yytext, yyleng, TK_SUMA);
    } else if(yytext[0] == '-'){
        //printf("%s TK_RESTA\n", yytext);
        return return makeToken(yytext, yyleng, TK_RESTA);;
    } else if(yytext[0] == '*'){
        //printf("%s TK_MULTI\n", yytext);
        return makeToken(yytext, yyleng, TK_MULTI);
    }else if(yytext[0] == '/'){
        //printf("%s TK_DIV\n", yytext);
        return makeToken(yytext, yyleng, TK_DIV);
    }
}

";" {
    //printf("%s TK_SEMICOLON\n", yytext);
    return makeToken(yytext, yyleng, TK_SEMICOLON); 
}

"//"[^\n]* BEGIN(INITIAL);
"/*" BEGIN(comment);

<comment>"*/" BEGIN(INITIAL);
<comment>.|\n /*NOTHING*/;
<comment><<EOF>> BEGIN(INITIAL);



. { return makeToken(yytext, yyeleng, TK_ERROR); }

[ |\t|\n]+                  /* ignore whitespace */;
%%

ExprLexer::ExprLexer(std::istream &in) : in(in){
    yylex_init_extra(&in, &scanner); 
}

ExprLexer::~ExprLexer() {
    yylex_destroy(scanner);
}

int ExprLexer::getLineNo() {
    return yyget_lineno(scanner);
}