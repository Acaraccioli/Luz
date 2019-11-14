%require "3.0"
%language "c++"
%parse-param {ExprLexer& lexer}
%parse-param {YYNODESTATE& state}
%parse-param {ASTNode*& stmtList}
%define parse.error verbose 
%define api.value.type variant
%define parser_class_name {Parser}
%define api.namespace {Expr}

%code requires{
    #include "expr_ast.h"
    #include <map>
    #include <vector>
    #include <unordered_map>
    class ExprLexer;

}

%{
    #include <stdio.h>
    #include <iostream>
    #include "expr_ast.h"

    #include "parser.h"

    #define yylex(arg) lexer.getNextToken(arg)

    namespace Expr{
        void Parser::error(const std::string& msg){
            std::cerr << msg << "\n";
        }

   

    }

    extern int yylineno;

%}

%token<int> NUMBER 
%token<std::string> IDENT
%token SUMA RESTA MULT DIV POWER
%token LEFTPAR RIGHTPAR
%token ESCRIBA SEMICOLON
%token ASIGNACION 
%token RW_SI RW_ENTONCES RW_SINO RW_FINSI
%token RW_MIENTRAS RW_HAGA RW_FINMIENTRAS  
%token IGUALDAD NOIGUAL 
%token MENORQUE MAYORQUE MENORQUEOIGUAL MAYORQUEOIGUAL 
%type<ASTNode*> expr term factor
%type<ASTNode*> if_stmt else_block stmt stmt_list
%token ERROR EOL
%%


input: stmt_list eol { stmtList = $1; }
;

eol: EOL
    | %empty
;

stmt_list: stmt_list EOL stmt { 
        $$ = state.blockStmtCreate($1,$3);
    }
    | stmt { $1->eval(); }
;

stmt: IDENT ASIGNACION expr {$$ = state.assignCreate($1,$3); }
    | ESCRIBA expr { $$ = state.printCreate($2); }
    | RW_MIENTRAS expr EOL RW_HAGA EOL stmt EOL RW_FINMIENTRAS { $$ = state.whileStmtCreate($2,$6); }
    | if_stmt
;

if_stmt: RW_SI expr RW_ENTONCES EOL stmt_list EOL else_block RW_FINSI { $$ = state.ifStmtCreate($2,$5,$7); }
;

else_block: RW_SINO EOL stmt EOL { $$ = $3; }
;

expr: expr IGUALDAD term { $$ = state.equalCreate($1,$3); }
    | expr NOIGUAL term { $$ = state.notequalCreate($1,$3); }
    | expr MENORQUE term { $$ = state.lessthanCreate($1,$3); }
    | expr MAYORQUE term { $$ = state.greaterthanCreate($1,$3); }
    | expr MENORQUEOIGUAL term { $$ = state.lessthanorequalCreate($1,$3); }
    | expr MAYORQUEOIGUAL term { $$ = state.greaterthanorequalCreate($1,$3); }
    | expr SUMA term { $$ = state.plusCreate($1,$3); }
    | expr RESTA term { $$ = state.minusCreate($1,$3); }
    | term { $$ = $1; }
;

term: term MULT factor { $$ = state.multiplyCreate($1,$3); } 
    | term DIV factor { $$ = state.divideCreate($1,$3); }
    | term POWER factor { $$ = state.powerCreate($1,$3); }
    | factor { $$ = $1; }
;

factor: NUMBER { $$ = state.intnumCreate($1); }
    | IDENT { $$ = state.identifierCreate($1); }
    | LEFTPAR expr RIGHTPAR { $$ = $2; }
;


%%
