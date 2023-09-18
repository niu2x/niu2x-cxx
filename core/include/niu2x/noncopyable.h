#ifndef NIU2X_NONCOPYABLE_H
#define NIU2X_NONCOPYABLE_H

#include <niu2x/api.h>

namespace niu2x {

class NXAPI Noncopyable {
public:
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}; // namespace niu2x

#endif