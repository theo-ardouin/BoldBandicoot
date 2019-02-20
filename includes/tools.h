#ifndef TOOLS_H_
#define TOOLS_H_

#include <lua.h>

void tools_lua_fatal(lua_State*);

void tools_execute_from(const char* filepath);

#endif
