%option noyywrap nodefault reentrant

%{
	#include <stdio.h>
	#include <jp-parser.h>
%}

%%

%error-verbose

[a-z] { return T_NAME; }
[0-9] { 
	YYSTYPE *token_value = (YYSTYPE *)yyget_extra(yyscanner);
	token_value->number = atoi(yytext); 
	return T_NUMBER; 
}
"=" { return '='; }
" " {}
\n {}
\r {}
\t {}
<<EOF>> { return T_EOF; }
. {return T_UNKNOWN;}

%%