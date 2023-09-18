#ifndef NIU2X_NONCOPYABLE_H
#define NIU2X_NONCOPYABLE_H

namespace niu2x {

class Noncopyable {
public:
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}; // namespace niu2x

#endif