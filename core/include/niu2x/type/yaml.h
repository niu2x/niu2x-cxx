#ifndef NIU2X_TYPE_YAML_H
#define NIU2X_TYPE_YAML_H

#include <niu2x/type/buffer.h>

namespace niu2x {

class YAMLImp;

class YAML {
public:
    static YAML parse(const String&);
    // YAML();
    ~YAML();

private:
    UniquePtr<YAMLImp> pimp_;
    explicit YAML(UniquePtr<YAMLImp>&&);
};

} // namespace niu2x

#endif