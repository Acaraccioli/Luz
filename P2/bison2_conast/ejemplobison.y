    /*
    //archivos es .y

    bison --defines=tokens.h -o expr_parser.cpp bison.y*/
    %define parse.error verbose
    %code requires {
        #include "expr_ast.h"
    }

    %{
    #include <stdio.h>
    #include <iostream>
    #include "expr_ast.h"
    extern int yylineno;
    static unordered_map<string, int> vars;
    int yylex();
    void yyerror( const char * error){
        //throw std::string("Line ")+ std::to_string(yylineno) + ": "+ error;
    }
    %}
    %union {
    ASTNode *tipo_astnode;
    int tipo_numero;
    char *tipo_string;
    };

    %token AddOp SubOp MultOp DivOp
    %token OpenPar ClosePar Semicolon
    %token<tipo_numero> Number
    %token Eof
    %token<tipo_string> Ident

    %type<tipo_astnode> input expr term factor

    %%
    stmt: input Semicolon stmt | %empty
    ;
    input : expr { std::cout<<$1->toString()<<"="<<$1->eval(vars)<<std::endl;}
    ;
    expr: expr AddOp term { $$ = new AddExpr($1, $3);}
    | expr SubOp term { $$ = new SubExpr($1, $3);}
    | term { $$ = $1;}
    ;
    term: term MultOp factor { $$ = new MulExpr($1 , $3);}
    | term DivOp factor { $$ = new DivExpr($1, $3);}
    | factor { $$ = $1;}
    ;
    factor : Number { $$ = new NumExpr($1);}
    | Ident { $$ = new IdentExpr($1); free($1);}
    | OpenPar expr ClosePar { $$ = new ParExpr($2);}
    ;
    %%