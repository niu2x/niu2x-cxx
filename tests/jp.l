%option noyywrap nodefault reentrant  

%{
	#include <stdio.h>
%}

%%

\n { return 1; }
\r { return 2; }
. { return 3; }

<<EOF>> { return EOF; }

%%