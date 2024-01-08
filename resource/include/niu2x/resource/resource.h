#ifndef NIU2X_RESOURCE_RESOURCE_H
#define NIU2X_RESOURCE_RESOURCE_H

#include <niu2x/serializable.h>
#include <niu2x/deserializable.h>
#include <niu2x/fs.h>

namespace niu2x {

class Resource : public Serializable, Deserializable {
public:
    void load_from_file(const fs::AbsPath& path);
    void store_to_file(const fs::AbsPath& path);
    virtual ~Resource() = 0;
};

} // namespace niu2x

#endif
