#ifndef NIU2X_PP_MOVABLE_H
#define NIU2X_PP_MOVABLE_H

#define NIU2X_PP_MOVABLE(clazz)                                                \
    clazz(clazz&&) = default;                                                  \
    clazz& operator=(clazz&&) = default;

#endif