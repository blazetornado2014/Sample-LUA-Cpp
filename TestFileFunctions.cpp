#include <iostream>
#include <string>

extern "C"
{
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "lua54.lib")
#endif 

bool CheckLua(lua_State* L, int r)
{
    if (r != LUA_OK)
    {
        std::string errmsg = lua_tostring(L, -1);
        std::cout << errmsg << std::endl;
        return false;
    }

    return true;
}

int main()
{
    struct Player {
        std::string name;
        std::string title;
        std::string family;
        int level;
    }player;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (CheckLua(L, luaL_dofile(L, "VideoExample.lua")))
    {
        lua_getglobal(L, "AddVar");
        if (lua_isfunction(L, -1))
        {
            lua_pushnumber(L, 3.5f);
            lua_pushnumber(L, 4.2f);

        }
        if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
        {
            std::cout << "[C++] Called in Lua AddVar, got " << (float)lua_tonumber(L, -1) << std::endl;
        }
    }

    lua_close(L);
    return 0;
}