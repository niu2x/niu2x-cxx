#ifndef NXC_LISP_H
#define NXC_LISP_H

struct lisp_t;
typedef struct lisp_t lisp_t;

lisp_t* lisp_alloc();
void lisp_free(lisp_t* self);

void lisp_create_symbol(const char*);

#endif