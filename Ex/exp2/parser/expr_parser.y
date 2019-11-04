%pure-parser

%code requires {
    using YYSTYPE = double;
    #define YYSTYPE_IS_DECLARED 1
}

%{
    #include "expr_parser.h"

    #define YYERROR_VERBOSE 1
    

    #define yylex(x) lexer.getNextToken(x)
    #define yyparse(x) ExprParser::parse()

    void ExprParser::yyerror(const char *msg) {
        cout << msg << endl;
    }

%}

%token NUMBER 
%token OPADD '+' 
%token OPSUB '-'
%token OPMUL '*'
%token OPDIV '/'
%token OPEN_PAR '('
%token CLOSED_PAR ')'
%token SEMI ';'
%%  

input: expr_list {std::cout << "input" << std::endl;} 
;

expr_list: expr_list opt_semi expr  {
        std::cout << "map size: "<<map.size() << "map val: " << $2<< std::endl;
        map.push_back($3);

    }
    | %empty {map.clear();}
    ;
opt_semi: ';' 
    | %empty {map.clear();}
;

expr: expr '+' term {
    //std::cout << "suma" << std::endl;
    double val = $1 + $3;
    std::cout << "res: "<<val << std::endl;
   std::cout << "val1: "<<$1 << "val2: "<<$3 << std::endl;
    $$ = val;
    }
    | expr '-' term {double val = $1 - $3;
    std::cout << "res -: "<<val << std::endl;
    $$ = val;}
    | term          {std::cout << "term" << std::endl;$$ = $1;}
    ;

term: term '*' factor {double val = $1 * $3;
    
    std::cout << "res *: "<<val << std::endl;
    $$ = val;}
    | term '/' factor {double val = $1 / $3;
    std::cout << "res /: "<<val << std::endl;
    std::cout << "cant"<<getExprCount() << std::endl;
   
    $$ = val;
    }
    | factor          {std::cout << "factor" << std::endl;$$ = $1;}
    ;

factor: NUMBER { $$ = $1; }
    | '(' expr ')' {$$ = $2;}
;

%%