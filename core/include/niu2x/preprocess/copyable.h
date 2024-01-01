#ifndef NIU2X_PP_COPYABLE_H
#define NIU2X_PP_COPYABLE_H

#define NIU2X_PP_COPYABLE(clazz)                                               \
    clazz(const clazz&) = default;                                             \
    clazz& operator=(const clazz&) = default;

#endif