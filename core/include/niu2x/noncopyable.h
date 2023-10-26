#ifndef NIU2X_NONCOPYABLE_H
#define NIU2X_NONCOPYABLE_H

#include <niu2x/api.h>

namespace niu2x {

/**
 * @brief       Interface of noncopyable classes*/
class NXAPI Noncopyable {
public:
    Noncopyable() { }
    ~Noncopyable() { }

    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;

    Noncopyable(Noncopyable&&) = default;
    Noncopyable& operator=(Noncopyable&&) = default;
};

}; // namespace niu2x

#endif