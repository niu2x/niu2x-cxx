#ifndef NIU2X_SINGLETON_H
#define NIU2X_SINGLETON_H

#include <niu2x/noncopyable.h>

namespace niu2x {

template <class T>
class Singleton : private Noncopyable {
public:
    Singleton() { }
    ~Singleton() { }
    static T* get()
    {
        static T instance;
        return &instance;
    }
};

} // namespace niu2x

#endif