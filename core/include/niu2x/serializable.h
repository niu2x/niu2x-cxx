#ifndef NIU2X_SERIALIZABLE_H
#define NIU2X_SERIALIZABLE_H

#include <niu2x/stream.h>

namespace niu2x {

class Serializable {
public:
    virtual ~Serializable() { }
    virtual void store_to(ByteWriteStream* dest) = 0;
};

} // namespace niu2x

#endif
