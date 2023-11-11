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

void LuaEngine::get_field(const String& field)
{
    lua_getfield(L(), -1, field.c_str());
}

void LuaEngine::pop(NR n) { lua_pop(L(), n); }

String LuaEngine::to_string()
{
    size_t len = 0;
    auto base = lua_tolstring(L(), -1, &len);
    return String(base, base + len);
}

double LuaEngine::to_number() { return lua_tonumber(L(), -1); }

LuaValue LuaEngine::read_field(const String& field)
{
    get_field(field);
    LuaValue result { NIL {} };

    if (is_number())
        result = to_number();
    else if (is_string())
        result = to_string();
    pop(1);
    return result;
}

bool LuaEngine::is_nil() { return lua_isnil(L(), -1); }
bool LuaEngine::is_string() { return lua_isstring(L(), -1); }
bool LuaEngine::is_number() { return lua_isnumber(L(), -1); }

NR LuaEngine::len() { return lua_objlen(L(), -1); }

void LuaEngine::get_field(Index i) { lua_rawgeti(L(), -1, i); }

} // namespace niu2x::lua
