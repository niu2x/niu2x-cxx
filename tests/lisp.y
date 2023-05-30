%define parse.error verbose
%define api.push-pull push
%define api.pure
%parse-param {void* nxc_parser} {void *userdata}

%token T_UNKNOWN
%token T_EOF
%token <str> T_NAME
%token <number> T_NUMBER

%nterm <value> value
%nterm <value> form

%{

#include <stdio.h>
#include <stdint.h>
#include "lisp.h"
#define LISP ((lisp_t*)userdata)

%}

%union {
    int number;
    char *str;
    struct lisp_value_t  value;
};

%%

start: block T_EOF {puts("reduce start");}

block: {} formlist {}

formlist: 
    | formlist1

formlist1: formlist1 form
    | form

form: { $<value>$.type = LISP_VALUE_FORM;  $<value>$.form = lisp_create_form(LISP);    } '(' valuelist1 ')' {}

valuelist1: value 
    | valuelist1 value

value: T_NAME { $$.symbol = lisp_create_symbol(LISP, $1); $$.type = LISP_VALUE_SYMBOL; printf("get symbol %d\n", $$); }
    | T_NUMBER  { $$.type = LISP_VALUE_NUMBER; $$.number = $1;}
    | form { $$.type = LISP_VALUE_FORM;  }

%%