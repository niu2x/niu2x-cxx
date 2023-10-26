#ifndef NIU2X_LUA_LUA_ENGINE_H
#define NIU2X_LUA_LUA_ENGINE_H

#include <niu2x/api.h>
#include <niu2x/noncopyable.h>
#include <niu2x/fs.h>

namespace niu2x::lua {

class NXAPI LuaEngine : Noncopyable {
public:
    LuaEngine();
    ~LuaEngine();

    int main(int argc, char* argv[]);

    void execute_file(const fs::Path& path);

private:
    void* L_;
};

} // namespace niu2x::lua

#endif