#ifndef NIU2X_DESERIALIZABLE_H
#define NIU2X_DESERIALIZABLE_H

#include <niu2x/type/stream.h>

namespace niu2x {

class NXAPI Deserializable {
public:
    virtual ~Deserializable() { }
    virtual void load_from(ReadStream* src) = 0;
};

} // namespace niu2x

#endif
