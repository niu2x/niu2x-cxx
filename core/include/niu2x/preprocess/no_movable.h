#ifndef NIU2X_PP_NO_MOVABLE_H
#define NIU2X_PP_NO_MOVABLE_H

#define NIU2X_PP_NO_MOVABLE(clazz)                                             \
    clazz(clazz&&) = delete;                                                   \
    clazz& operator=(clazz&&) = delete;

#endif