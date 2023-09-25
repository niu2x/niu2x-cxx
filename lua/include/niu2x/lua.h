#ifndef NIU2X_LUA_H
#define NIU2X_LUA_H

#include <niu2x/api.h>
#include <niu2x/noncopyable.h>

namespace niu2x::lua {

class LuaEngine: Noncopyable {
public:	
	LuaEngine(); 
	~LuaEngine(); 

private:
	void *L_;
};

}

#endif