#ifndef NXC_NONCOPYABLE_H
#define NXC_NONCOPYABLE_H

namespace niu2x::core {

class Noncopyable {
public:
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}; // namespace niu2x::core

#endif