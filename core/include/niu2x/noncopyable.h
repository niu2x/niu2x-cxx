#ifndef NIU2X_NONCOPYABLE_H
#define NIU2X_NONCOPYABLE_H

#include <niu2x/preprocess.h>

namespace niu2x {

/**
 * @brief       Interface of noncopyable classes*/
class Noncopyable {
public:
    Noncopyable() { }
    ~Noncopyable() { }

    NIU2X_PP_NO_COPYABLE(Noncopyable)

    NIU2X_PP_MOVABLE(Noncopyable)
};

}; // namespace niu2x

#endif