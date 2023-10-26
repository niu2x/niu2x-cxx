#include <niu2x/lua/lua_engine.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/unused.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#define L() reinterpret_cast<lua_State*>((L_))

namespace niu2x::lua {

LuaEngine::LuaEngine()
{
    L_ = lua_open();
    if (!L_) {
        throw BadAlloc();
    }
}

LuaEngine::~LuaEngine() { lua_close(L()); }

void LuaEngine::execute_file(const fs::Path& path) { unused(path); }

int LuaEngine::main(int argc, char* argv[]) { return lua_main(argc, argv); }

} // namespace niu2x::lua
