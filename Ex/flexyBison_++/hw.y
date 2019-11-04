%require "3.0"
%language "c++"
%parse-param {ExprLexer& lexer}
%parse-param {std::unordered_map<std::string, int> idents}
%define parse.error verbose 
%define api.value.type variant
%define parser_class_name {Parser}
%define api.namespace {Expr}

%code requires{
    #include <unordered_map>
    class ExprLexer;

}

%{
    #include <stdio.h>
    #include <iostream>
       
     #include "parser.h"

    #define yylex(arg) lexer.getNextToken(arg)

    namespace Expr{
        void Parser::error(const std::string& msg){
            std::cerr << msg << "\n";
        }
    }

    extern int yylineno;

   /* void yyerror(const char * e){
        throw std::string("Line ") + std::to_string(yylineno) + ": " + e + "\n";
    } */

%}

%token<int> TK_NUMBER 
%token TK_ERROR TK_EOL
%token<std::string> TK_IDENT
%token TK_SUMA TK_RESTA TK_MULTI TK_DIV 
%token TK_LEFTPAR TK_RIGHTPAR
%token TK_PRINT TK_SEMICOLON
%token TK_ASSIGN TK_IF 

%type<int> expr term factor

%%

input: stmt_list opt_semi
;

opt_semi: TK_SEMICOLON
    | %empty
;

stmt_list: stmt_list TK_SEMICOLON stmt
    | stmt { }
;

stmt: TK_IDENT TK_ASSIGN expr { idents[$1] = $3; }
    | TK_PRINT expr { std::cout << $2 << std::endl; }
;

expr: expr TK_SUMA term { $$ = $1 + $3; }
    | expr TK_RESTA term { $$ = $1 - $3; }
    | term { $$ = $1; }
;

term: term TK_MULTI factor { $$ = $1 * $3; } 
    | term TK_DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor: TK_NUMBER { $$ = $1; }
    | TK_IDENT { $$ = idents[$1]; }
    | TK_LEFTPAR expr TK_RIGHTPAR { $$ = $2; }
;

%%
