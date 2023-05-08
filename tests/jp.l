%option noyywrap nodefault reentrant  

%{
	#include <stdio.h>
	#include <jp-parser.h>
%}

%%

[a-z] { return T_NAME; }
[0-9] { return T_NAME; }
'=' { return '='; }

<<EOF>> { return T_EOF; }

%%