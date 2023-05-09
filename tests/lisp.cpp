
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "lisp.h"
}

struct lisp_t {
};

lisp_t* lisp_alloc()
{
    lisp_t* self = (lisp_t*)malloc(sizeof(lisp_t));
    return self;
}

void lisp_free(lisp_t* self) { free(self); }

void lisp_create_symbol(const char* name)
{
    printf("lisp_create_symbol %s\n", name);
}