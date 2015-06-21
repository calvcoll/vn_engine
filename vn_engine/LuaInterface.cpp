#include "LuaInterface.h"

lua_State* initLuaScript(char* filename) {
	lua_State* state;
	
	state = luaL_newstate();
	luaL_openlibs(state);

	int status = luaL_loadfile(state, filename);
	if (status == 0) {
		status = lua_pcall(state, 0, LUA_MULTRET, 0);
	}

	checkErrors(state, status);
	return state;
}

void checkErrors(lua_State* state, int status) {
	if (status != 0) {
		std::cerr << "Lua Error: " << lua_tostring(state, -1) << std::endl;
		lua_pop(state, 1);
	}
}

void killLuaState(lua_State* state) {
	lua_close(state);
}