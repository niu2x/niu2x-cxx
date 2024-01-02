#ifndef NIU2X_RESOURCE_H
#define NIU2X_RESOURCE_H

#include <niu2x/serializable.h>
#include <niu2x/deserializable.h>

namespace niu2x {

class Resource : public Serializable, Deserializable {
public:
    virtual ~Resource() = 0;
};

} // namespace niu2x

#endif