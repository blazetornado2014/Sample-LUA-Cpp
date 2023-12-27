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
        lua_getglobal(L, "player");
        if (lua_istable(L, -1))
        {
            lua_pushstring(L, "Name");
            lua_gettable(L, -2);
            player.name = lua_tostring(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "Title");
            lua_gettable(L, -2);
            player.title = lua_tostring(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "Family");
            lua_gettable(L, -2);
            player.family = lua_tostring(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "Level");
            lua_gettable(L, -2);
            player.level = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
    }
    std::cout << player.title << " " << player.name << " of " << player.family << " Level " << player.level << std::endl;

    lua_close(L);
    return 0;
}