#ifndef NIU2X_LUA_LUA_ENGINE_H
#define NIU2X_LUA_LUA_ENGINE_H

#include <niu2x/api.h>
#include <niu2x/noncopyable.h>

namespace niu2x::lua {

class NXAPI LuaEngine : Noncopyable {
public:
    LuaEngine();
    ~LuaEngine();
    int main(int argc, char* argv[]);

private:
    void* L_;
};

} // namespace niu2x::lua

#endif