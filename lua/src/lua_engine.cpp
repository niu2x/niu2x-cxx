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

    luaL_openlibs(L());
}

LuaEngine::~LuaEngine() { lua_close(L()); }

bool LuaEngine::execute_file(const fs::Path& path)
{
    fs::File script_file(path);
    if (!script_file.exists()) {
        throw fs::FileNotExists(path);
    }
    auto buf = script_file.as_buffer(true);
    bool succ = !luaL_dostring(L(), reinterpret_cast<const char*>(buf.data()));
    return succ;
}

int LuaEngine::main(int argc, char* argv[]) { return lua_main(argc, argv); }

void LuaEngine::get_global(const String& field)
{
    lua_getglobal(L(), field.c_str());
}

void LuaEngine::set_global(const String& field)
{
    lua_setglobal(L(), field.c_str());
}

} // namespace niu2x::lua
