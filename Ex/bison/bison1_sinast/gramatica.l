%option noyywrap
%option yylineno
%x comment
%{
#include <stdio.h>
#include "tokens.h"       

%}

%%
"//"(.*) ;
"/*" BEGIN(comment);
<comment>"*/" BEGIN(INITIAL);
<comment>.|\n /*nada*/ ; 
<comment><<EOF>> BEGIN(INITIAL);

[0-9]+ { 
    yylval=atoi(yytext);
return Number;

}
\n { }

"(" { 
return OpenPar;

}
")" { 
return ClosePar;

}
"+" { 
return AddOp;

}
"-" { 
return SubOp;

}
"*" { 
return MultOp;

}
"/" { 
return DivOp;

}
";" { 
return Semicolon;

}


%%


//flex -o ejemplo1.c ejemplo1.l
//gcc -o ejemplo ejemplo1.c
//./ejemplo


//"//"[^\n]+ comentarios_de_linea++;
