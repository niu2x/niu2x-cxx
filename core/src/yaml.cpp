#include "rapidyaml.h"
#include <niu2x/type/yaml.h>
#include <niu2x/noncopyable.h>

namespace niu2x {

class YAMLImp : private Noncopyable {
public:
    explicit YAMLImp(const String& sz)
    {
        auto s = ryml::csubstr(sz.c_str(), sz.size());
        tree_ = ryml::parse_in_arena(s);
        root_ = tree_.crootref();
    }
    ~YAMLImp() { }

private:
    ryml::Tree tree_;
    ryml::ConstNodeRef root_;
};

YAML::YAML(UniquePtr<YAMLImp>&& other)
: pimp_(std::move(other))
{
}

// YAML::YAML()
// : pimp_(nullptr)
// {
// }
YAML::~YAML() { }
YAML YAML::parse(const String& sz) { return YAML(make_unique<YAMLImp>(sz)); }

} // namespace niu2x
