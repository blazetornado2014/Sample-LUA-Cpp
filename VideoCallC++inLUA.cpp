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

int HostFunction(lua_State* L)
{
    float a = lua_tonumber(L, 1);
    float b = lua_tonumber(L, 2);
    std::cout << "[C++] HostFunction(" << a << ", " << b << ") called" << std::endl;

    float c = a * b;
    lua_pushnumber(L, c);

    return 1;
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

    lua_register(L, "HostFunction", HostFunction);

    if (CheckLua(L, luaL_dofile(L, "VideoExample.lua")))
    {
        lua_getglobal(L, "DoSomething");
        if (lua_isfunction(L, -1))
        {
            lua_pushnumber(L, 1);
            lua_pushnumber(L, 4);

            if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
            {
                std::cout << "[C++] Called DoSomething(a, b), got " << (float)lua_tonumber(L, -1) << std::endl;
            }
        }
    }

    lua_close(L);
    return 0;
}