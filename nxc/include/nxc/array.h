#ifndef NXC_ARRAY_H
#define NXC_ARRAY_H

#define NXC_ARRAY_DECLARE(st_name) struct st_name;

#define NXC_ARRAY_DEFINE(st_name, elem_t)                                      \
    struct st_name {                                                           \
        elem_t* base;                                                          \
        int nr;                                                                \
        int alloc;                                                             \
    };                                                                         \
    void st_name##_init(st_name* self)                                         \
    {                                                                          \
        self->base = nullptr;                                                  \
        self->nr = self->alloc = 0;                                            \
    }

#endif