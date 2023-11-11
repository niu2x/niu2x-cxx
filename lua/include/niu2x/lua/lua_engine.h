#ifndef NIU2X_LUA_LUA_ENGINE_H
#define NIU2X_LUA_LUA_ENGINE_H

#include <niu2x/api.h>
#include <niu2x/noncopyable.h>
#include <niu2x/fs.h>

namespace niu2x::lua {

struct NIL {
};
using LuaValue = Variant<String, double, NIL>;

class NXAPI LuaEngine : Noncopyable {
public:
    LuaEngine();
    ~LuaEngine();
    int main(int argc, char* argv[]);
    bool execute_file(const fs::Path& path);
    // void fetch_config();

    // high-level api
    LuaValue read_field(const String& field);

    // low-level lua api
    void get_global(const String& field);
    void set_global(const String& field);
    void get_field(const String& field);
    void get_field(Index i);
    void pop(NR n);
    String to_string();
    double to_number();
    bool is_nil();
    bool is_string();
    bool is_number();
    NR len();

private:
    void* L_;
};

} // namespace niu2x::lua

#endif