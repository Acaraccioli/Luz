%require "3.0"
%language "c++"
%parse-param {ExprLexer& lexer}
%parse-param {YYNODESTATE& state}
%parse-param { ASTNode* &stmtList }
%define parse.error verbose 
%define api.value.type variant
%define api.parser.class {Parser}
%define api.namespace {Expr}

%code requires{
    #include "expr_ast.h"
    #include <unordered_map>
    #include <vector>
    class ExprLexer;
    //YYNODESTATE * state;
}

%{
    #include <stdio.h>
    #include <iostream>
    #include "expr_ast.h"
    #include "expr_parser.h"
    #define yylex(arg) lexer.getNextToken(arg)

    namespace Expr{
        void Parser::error(const std::string& msg){
            std::cerr << msg << "\n";
        }
    }

    extern int yylineno;
%}

%token<int> TK_NUMBER 
%token TK_ERROR TK_EOL
%token<std::string> TK_IDENT
%token TK_SUMA TK_RESTA TK_MULTI TK_DIV TK_POWER
%token TK_LEFTPAR TK_RIGHTPAR
%token TK_PRINT TK_SEMICOLON
%token TK_ASSIGN 
%token<std::string> TK_STRING
%token TK_IF TK_THEN TK_ELSE TK_ENDIF
%token TK_WHILE TK_DO TK_ENDWHILE  
%token OP_EQUAL 
%token OP_NOTEQUAL 
%token OP_LESSTHAN 
%token OP_GREATERTHAN 
%token OP_LESSTHANEQUAL
%token OP_GREATERTHANEQUAL TK_EOF

%type<ASTNode*> expr term factor
%type<ASTNode*> if_stmt else_block stmt stmt_list input

%%

input: stmt_list eol { stmtList = $1; }
;

eol: TK_EOL
    | %empty
;

stmt_list: stmt_list eol stmt eol { 
        $$ = state.blockStmtCreate($1,$3);
        $$->AST2CFG();
    }
    | stmt { $$ = $1;}
    | %empty { $$ = state.nopCreate(); }
;

stmt: TK_IDENT TK_ASSIGN expr { $$ = state.assignCreate($1,$3);  }
    | TK_PRINT expr { $$ = state.printCreate($2); }
    | TK_WHILE expr eol TK_DO eol stmt_list eol TK_ENDWHILE { $$ = state.whileStmtCreate($2,$6); }
    | if_stmt
;

if_stmt: TK_IF expr TK_THEN TK_EOL stmt_list eol else_block TK_ENDIF { $$ = state.ifStmtCreate($2,$5,$7); }
;

else_block: TK_ELSE TK_EOL stmt TK_EOL { $$ = $3; }
;

expr:  expr TK_SUMA term { $$ = state.plusCreate($1,$3); }
    | expr TK_RESTA term { $$ = state.minusCreate($1,$3); }
    | term { $$ = $1; }
;

term:  factor { $$ = $1; }
;

factor: TK_NUMBER { $$ = state.intnumCreate($1); }
    | TK_IDENT { $$ = state.idCreate($1); }
    | TK_LEFTPAR expr TK_RIGHTPAR { $$ = $2; }
;


%%