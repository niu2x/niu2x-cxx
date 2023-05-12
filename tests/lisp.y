%define parse.error verbose
%define api.push-pull push
%define api.pure
%parse-param {void* nxc_parser} {void *userdata}

%token T_UNKNOWN
%token T_EOF
%token <str> T_NAME
%token <number> T_NUMBER

%nterm <value> value


%{

#include <stdio.h>
#include <stdint.h>
#include "lisp.h"

#define LISP ((lisp_t*)userdata)

%}


%union {
    int number;
    char *str;
    uint64_t value;
};

%%


start: block T_EOF {puts("reduce start");}

block: formlist

formlist: 
    | formlist1

formlist1: formlist1 form
    | form

form: '(' valuelist1 ')'

valuelist1: value
    | valuelist1 value

value: T_NAME { $$ = lisp_create_symbol(LISP, $1);  printf("get symbol %d\n", $$); }
    | T_NUMBER  {$$ = 0;}
    | form {$$ = 0;}

%%