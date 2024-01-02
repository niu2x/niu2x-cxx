#ifndef NIU2X_DESERIALIZABLE_H
#define NIU2X_DESERIALIZABLE_H

#include <niu2x/base_stream.h>

namespace niu2x {

class Deserializable {
public:
    virtual ~Deserializable() { }
    virtual void load_from(ByteReadStream* src) = 0;
};

} // namespace niu2x

#endif
