#include <niu2x/lua.h>

using namespace niu2x;

int main(int argc, char* argv[])
{
    lua::LuaEngine lua_engine;
    return lua_engine.main(argc, argv);
}