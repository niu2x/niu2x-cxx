%define api.push-pull push
%define api.pure

%token T_EOF
%token T_NAME
%token <number> T_NUMBER


%{

#include <jp-lexer.h>

%}

%union {
    int number;
};

%%

start: stmt T_EOF

stmt: T_NAME '=' T_NUMBER

%%