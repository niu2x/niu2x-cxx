%option noyywrap nodefault reentrant

%top{
	#include "lisp.h"
}

%{
	#include <stdio.h>
	#include <lisp-parser.h>
	#define yylval ((YYSTYPE *)yyget_extra(yyscanner))
%}


digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit})*

%%

{identifier} {
	yylval->str = yytext;
	return T_NAME; 
}

[0-9] { 
	yylval->number = atoi(yytext); 
	return T_NUMBER; 
}

"=" { return '='; }
"(" { return '('; }
")" { return ')'; }

" " {}
\n {}
\r {}
\t {}
<<EOF>> { return T_EOF; }
. {return T_UNKNOWN;}

%%