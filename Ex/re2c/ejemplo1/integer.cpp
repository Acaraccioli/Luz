/* Generated by re2c 1.2.1 on Tue Oct 29 18:36:46 2019 */
#line 1 "trabajoclase1.re"
#include <stdio.h>
enum num_t {ERR,BIN,OCT,DEC,HEX};

static num_t lex(const char * YYCURSOR)
{
	const char *YYMARKER;

#line 11 "integer.cpp"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
	case '0':	goto yy4;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
#line 15 "trabajoclase1.re"
	{return ERR;}
#line 24 "integer.cpp"
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x00:	goto yy5;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy7;
	case 'B':
	case 'b':	goto yy10;
	default:	goto yy3;
	}
yy5:
	++YYCURSOR;
#line 16 "trabajoclase1.re"
	{return OCT;}
#line 45 "integer.cpp"
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy5;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy7;
	default:	goto yy9;
	}
yy9:
	YYCURSOR = YYMARKER;
	goto yy3;
yy10:
	yych = *++YYCURSOR;
	if (yych <= 0x00) goto yy9;
	goto yy12;
yy11:
	yych = *++YYCURSOR;
yy12:
	switch (yych) {
	case 0x00:	goto yy13;
	case '0':
	case '1':	goto yy11;
	default:	goto yy9;
	}
yy13:
	++YYCURSOR;
#line 17 "trabajoclase1.re"
	{return BIN;}
#line 80 "integer.cpp"
}
#line 19 "trabajoclase1.re"


}

int main(int argc, char **argv)
{
	int i;
for(i=1;i<argc;++i)
{
switch(lex(argv[i])){

case BIN: printf("binario!"); break;
default: break;


}
}
}
//re2c -o integers.cpp integers.re
//g++ -o integers integers.cpp

