
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "lisp.h"
}

#define NEW_ALLOC(nr, alloc, new_size) ((new_size)*2)

struct String {
    String* next;
    uint64_t hash;
    uint8_t mark;
    char str[0];
};

struct StringTable {
    String* base;
    int nr;
};

struct SymbolTable {
    String** base;
    int nr;
    int alloc;
};

struct Form {
    lisp_value_t* base;
    int nr;
    int alloc;
};

struct FormTable {
    Form** base;
    int nr;
    int alloc;
};

struct lisp_t {
    StringTable string_table;
    SymbolTable symbol_table;
    FormTable form_table;
};

static void StringTable_init(StringTable* self);
static String* StringTable_create_string(
    StringTable* self, const char* sz, int len = 0);

static uint64_t hash(const uint8_t* str);

static void SymbolTable_init(SymbolTable* self);
static void SymbolTable_resize(SymbolTable* self, int new_size);
static uint64_t SymbolTable_add_symbol(SymbolTable* self, String* str);

static void FormTable_init(FormTable* self);
static void FormTable_resize(FormTable* self, int new_size);
static uint64_t FormTable_new_form(FormTable* self);

static Form* form_create();

lisp_t* lisp_alloc()
{
    lisp_t* self = (lisp_t*)malloc(sizeof(lisp_t));
    StringTable_init(&self->string_table);
    SymbolTable_init(&self->symbol_table);
    FormTable_init(&self->form_table);
    return self;
}

void lisp_free(lisp_t* self) { free(self); }

uint64_t lisp_create_symbol(lisp_t* lisp, const char* name)
{
    String* str = StringTable_create_string(&lisp->string_table, name);
    return SymbolTable_add_symbol(&lisp->symbol_table, str);
}

uint64_t lisp_create_form(lisp_t* lisp)
{
    lisp_value_t form;
    form.type = LISP_VALUE_FORM;
    form.form = FormTable_new_form(&(lisp->form_table));
    return form.form;
}

static void StringTable_init(StringTable* self)
{
    self->nr = 511;
    self->base = (String*)malloc(sizeof(String) * self->nr);
    for (int i = 0; i < self->nr; i++) {
        self->base[i].next = nullptr;
    }
}

static String* StringTable_create_string(
    StringTable* self, const char* sz, int len)
{
    if (len <= 0) {
        len = strlen(sz);
    }

    uint64_t sz_hash = hash((const uint8_t*)sz);
    uint64_t index = sz_hash % self->nr;

    String* pptr = &self->base[index];
    String* ptr = pptr->next;
    while (ptr) {
        if (ptr->hash == sz_hash && strcmp(ptr->str, sz) == 0) {
            return ptr;
        }
        pptr = ptr;
        ptr = ptr->next;
    }

    String* new_string = (String*)malloc(sizeof(String) + len + 1);
    new_string->hash = sz_hash;
    new_string->next = nullptr;
    memcpy(new_string->str, sz, len);
    new_string->str[len] = 0;
    pptr->next = new_string;
    return new_string;
}

static uint64_t hash(const uint8_t* str)
{
    uint64_t hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

static void SymbolTable_init(SymbolTable* self)
{
    self->base = nullptr;
    self->nr = 0;
    self->alloc = 0;
}

static void SymbolTable_resize(SymbolTable* self, int new_size)
{
    if (new_size > self->alloc) {
        int new_alloc = NEW_ALLOC(self->nr, self->alloc, new_size);
        self->base = (String**)realloc(self->base, sizeof(String*) * new_alloc);
        self->alloc = new_alloc;
    }

    self->nr = new_size;
}

static uint64_t SymbolTable_add_symbol(SymbolTable* self, String* str)
{
    for (int i = 0; i < self->nr; i++) {
        if (self->base[i] == str)
            return i;
    }

    SymbolTable_resize(self, self->nr + 1);
    self->base[self->nr - 1] = str;
    return self->nr - 1;
}

static void FormTable_init(FormTable* self)
{
    self->base = nullptr;
    self->nr = 0;
    self->alloc = 0;
}

static void FormTable_resize(FormTable* self, int new_size)
{
    if (new_size > self->alloc) {
        int new_alloc = NEW_ALLOC(self->nr, self->alloc, new_size);
        self->base = (Form**)realloc(self->base, sizeof(Form*) * new_alloc);
        self->alloc = new_alloc;
    }

    self->nr = new_size;
}

static uint64_t FormTable_new_form(FormTable* self)
{
    FormTable_resize(self, self->nr + 1);
    auto* form = form_create();
    self->base[self->nr - 1] = form;
    return self->nr - 1;
}

static Form* form_create()
{
    Form* self = (Form*)malloc(sizeof(Form));
    self->base = nullptr;
    self->nr = 0;
    return self;
}

void lisp_push_form(lisp_t* lisp, uint64_t id) { }

uint64_t lisp_pop_form(lisp_t* lisp) { }
