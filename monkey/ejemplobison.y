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
        throw std::string("Line ")+ std::to_string(yylineno) + ": "+ error;
    }
    %}
    %union {
    ASTNode *tipo_astnode;
    int tipo_numero;
    char *tipo_string;
    };

    %token AddOp SubOp MultOp DivOp Igualdad
    %token OpenPar ClosePar Semicolon EndOfLine Igual Si Entonces Sino
    %token<tipo_numero> Number
    %token Eof Print
    %token<tipo_string> Ident

    %type<tipo_astnode> input expr term factor stmt_list stmt

    %%
        input:  stmt_list   opt_eol ;

        opt_eol: EndOfLine | %empty
        ;
        stmt_list : stmt_list  EndOfLine stmt 
                    | stmt 
        ;
        stmt : Ident Igual expr { $$ = new AssignStatement($1, $3);  std::cout<<"Assign Statement "<<$1<<"<-"<<$3->toString()<<std::endl;}
                | Print expr { $$ = new PrintStatement2($2);  std::cout<<"Print"<<"("<<$2->eval(vars)<<")"<<std::endl;}
                | Si expr Entonces stmt_list Sino stmt_list { $$ = new IfStatement($2, $4, $6);  std::cout<<"Si "<<$2->toString()<<"Entonces"<<std::endl;}
        ;
        expr :   expr AddOp term { $$ = new AddExpr($1,$3);}
                | expr SubOp term { $$ = new SubExpr($1,$3);}
                | term {$$ = $1;}
                | term Igualdad expr
        ;
        term : term MultOp factor { $$ = new MulExpr($1,$3);}
                | term DivOp factor { $$ = new DivExpr($1,$3);}
                | factor {$$ = $1;}
        ;
        factor : Ident   {$$ = new IdentExpr($1);}
                | Number { $$ = new NumExpr($1);}
                | OpenPar expr ClosePar  {$$ = new ParExpr($2);}
        ;
    %%