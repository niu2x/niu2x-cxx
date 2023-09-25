#include <niu2x/lua/lua_engine.h>
#include <niu2x/type/std_alias.h>

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

} // namespace niu2x::lua
