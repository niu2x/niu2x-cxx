#ifndef NIU2X_PREPROCESS_CLASS_UTILS_H
#define NIU2X_PREPROCESS_CLASS_UTILS_H

#define NIU2X_CLASS_DEFAULT_COPYABLE(clazz)                                    \
    clazz(const clazz&) = default;                                             \
    clazz& operator=(const clazz&) = default;

#define NIU2X_CLASS_DEFAULT_MOVABLE(clazz)                                     \
    clazz(clazz&&) = default;                                                  \
    clazz& operator=(clazz&&) = default;

#endif