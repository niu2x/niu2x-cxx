#ifndef NXC_LISP_H
#define NXC_LISP_H

#include <stdint.h>

struct lisp_t;
typedef struct lisp_t lisp_t;

enum {
    LISP_VALUE_SYMBOL,
    LISP_VALUE_NUMBER,
    LISP_VALUE_FORM,
};

lisp_t* lisp_alloc();
void lisp_free(lisp_t* self);

uint64_t lisp_create_symbol(lisp_t* lisp, const char*);
uint64_t lisp_create_form(lisp_t* lisp);

struct lisp_value_t {
    int type;
    union {
        uint64_t symbol;
        int number;
        uint64_t form;
    };
};

#endif