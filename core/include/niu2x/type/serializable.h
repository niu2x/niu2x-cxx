#ifndef NIU2X_SERIALIZABLE_H
#define NIU2X_SERIALIZABLE_H

#include <niu2x/type/stream.h>

namespace niu2x {

class NXAPI Serializable {
public:
    virtual ~Serializable() { }
    virtual void store_to(WriteStream* src) = 0;
};

} // namespace niu2x

#endif
