%{
#include <cstdio>
#include <sstream>
#include <unordered_map>
#include "expr_lexer.h"

using namespace std;

extern char* yytext;

extern ExprLexer yylex;
extern std::ostringstream sout;

std::unordered_map<std::string, int> vars;

void yyerror(const char* msg){
    throw msg;
}

%}

%token TK_IDENT
%token OP_ASSIGN
%token TK_OPEN_PAR
%token TK_CLOSE_PAR
%token TK_NUMBER
%token TK_EOL
%token TK_EOF
%token KW_PRINT
%token OP_ADD
%token OP_SUB
%token OP_MUL
%token OP_DIV

%%

input: stmt_list opt_eol;

opt_eol: TK_EOL
         | %empty;

stmt_list: stmt_list TK_EOL stmt
            | stmt ;

stmt: TK_IDENT OP_ASSIGN expr { vars[yylex.idval] = $3;}
        | KW_PRINT expr { sout<<$2; };

expr: expr OP_ADD term { $$ = $1 + $3;}
        | expr OP_SUB term { $$ = $1 - $3;}
        | term { $$ = $1;};

term: term OP_MUL factor { $$ = $1 * $3;}
        | term OP_DIV factor { $$ = $1 / $3;}
        | factor { $$ = $1;};

factor: TK_IDENT { $$ = vars[yylex.idval]; }
        | TK_NUMBER { $$ = yylex.intVal;}
        | TK_OPEN_PAR expr TK_CLOSE_PAR { $$ = $2;};

%%