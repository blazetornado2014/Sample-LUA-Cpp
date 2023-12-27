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
    std::string cmd = "a = 7 + 11 + math.sin(23.7)";

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (CheckLua(L, luaL_dostring(L, cmd.c_str())))
    {
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            float a_cpp = (float)lua_tonumber(L, -1);
            std::cout << "a_cpp = " << a_cpp << std::endl;
        }
    }
    cmd = "a = a + 100";

    if (CheckLua(L, luaL_dostring(L, cmd.c_str())));

    lua_getglobal(L, "a");
    if (lua_isnumber(L, -1))
    {
        float a_cpp = (float)lua_tonumber(L, -1);
        std::cout << "a_cpp = " << a_cpp << std::endl;
    }

    lua_close(L);
    return 0;
}