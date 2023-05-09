%define api.push-pull push
%define api.pure
%parse-param {void* myParam}

%token T_UNKNOWN
%token T_EOF
%token T_NAME
%token <number> T_NUMBER


%{

#include <jp-lexer.h>
#include <stdio.h>

%}

%union {
    int number;
};

%%

start: stmtlist T_EOF {puts("reduce start");}

stmtlist: 
    | stmtlist1

stmtlist1: stmtlist1 stmt
    | stmt

stmt: T_NAME '=' T_NUMBER

%%