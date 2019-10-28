/*
//archivos es .y

bison --defines=tokens.h -o expr_parser.cpp ejemplobison.y*/
%define parse.error verbose


%{
#include <stdio.h>
extern int yylineno;
int yylex();
void yyerror( const char * error){
    //throw std::string("Line ")+ std::to_string(yylineno) + ": "+ error;
}
%}

%token AddOp SubOp MultOp DivOp
%token OpenPar ClosePar Semicolon
%token Number Eof

%%
stmt: input Semicolon stmt | ;
input : expr { printf("%d\n", $1);}
;
expr: expr AddOp term { $$ = $1 + $3;}
 | expr SubOp term { $$ = $1 - $3;}
 | term { $$ = $1;}
;
 term: term MultOp factor { $$ =$1 * $3;}
 | term DivOp factor { $$ = $1 / $3;}
 | factor { $$ = $1;}
;
 factor : Number { $$ = $1;}
 | OpenPar expr ClosePar { $$ = $2;}
 ;
%%