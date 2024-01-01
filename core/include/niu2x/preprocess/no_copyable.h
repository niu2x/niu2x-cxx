#ifndef NIU2X_PP_NO_COPYABLE_H
#define NIU2X_PP_NO_COPYABLE_H

#define NIU2X_PP_NO_COPYABLE(clazz)                                            \
    clazz(const clazz&) = delete;                                              \
    clazz& operator=(const clazz&) = delete;

#endif