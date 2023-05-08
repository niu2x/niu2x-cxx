%option noyywrap nodefault reentrant  

%%

\n { putchar(*yytext); }
\r { putchar(*yytext); }
. { putchar(*yytext); }

<<EOF>> { return 0; }

%%