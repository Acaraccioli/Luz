%option noyywrap
%option reentrant


%x lineComment
%x blockComment

%{
    #include "expr_lexer.h"

    #define YY_EXTRA_TYPE std::istream*
    #define YY_DECL Token ExprLexer::_getNextToken(yyscan_t yyscanner)
    #define YY_INPUT(buf, result, max_size)\
        do {\
            istream *in = yyget_extra(yyscanner);\
            in->read(buf, max_size); \
            result = in->gcount();\
        } while(0)

%}

%%

[0-9]+|[0-9]+"."[0-9]+ { text = yytext; return Token::Num; }

[_a-zA-Z][_0-9a-zA-Z]+ { text = yytext; return Token::Id; }

"+" {text = yytext; return Token::OpAdd; }
"-" { text = yytext;return Token::OpSub; }
"(" { text = yytext;return Token::OpenPar; }
")" { text = yytext;return Token::ClosePar; }
";" { text = yytext;return Token::Semicolon; }
"--" {BEGIN(lineComment);}
"(*" {BEGIN(blockComment);}

<<EOF>> { return Token::Eof; }

<lineComment>. { }
<lineComment>\n {BEGIN(INITIAL);}


<blockComment>\n { }
<blockComment>. { }
<blockComment>"*)" { BEGIN(INITIAL); }






%%

ExprLexer::ExprLexer(istream& in) : in(in){
    yylex_init_extra(&in, &scanner);
}

ExprLexer::~ExprLexer() {

}