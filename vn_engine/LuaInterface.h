#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include <lua.hpp>
#include <iostream>

lua_State* initLuaScript(char* filename);
void checkErrors(lua_State* state, int status);
void killLuaState(lua_State* state);

#endif