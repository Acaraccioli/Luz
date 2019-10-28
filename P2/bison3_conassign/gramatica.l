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
    yylval.tipo_numero=atoi(yytext);
return Number;
}
"Print" {
    return Print;
}
[_a-zA-Z][a-zA-Z0-9_]*  {
    yylval.tipo_string=strdup(yytext);
    return Ident;
}


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

[\n] {
    return EndOfLine;
}

"=" {
    return Igual;
}

%%


//flex -o ejemplo1.c ejemplo1.l
//gcc -o ejemplo ejemplo1.c
//./ejemplo


//"//"[^\n]+ comentarios_de_linea++;
