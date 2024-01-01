#ifndef NIU2X_FACTORY_H
#define NIU2X_FACTORY_H

namespace niu2x {

template <class T>
class Factory {
public:
    virtual ~Factory() { }
    virtual T* create_obj() = 0;
    virtual void destory_obj(T*) = 0;
};

} // namespace niu2x

#endif