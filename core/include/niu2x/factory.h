#ifndef NIU2X_FACTORY_H
#define NIU2X_FACTORY_H

#include <niu2x/std_alias.h>

namespace niu2x {

template <class T>
class RawPtrFactory {
public:
    virtual ~RawPtrFactory() { }
    virtual T* create_obj(const String& name) = 0;
    virtual void destory_obj(T*) = 0;
};

template <class T>
class UPtrFactory {
public:
    virtual ~UPtrFactory() { }
    virtual UniquePtr<T> create_obj(const String& name) = 0;
};

} // namespace niu2x

#endif