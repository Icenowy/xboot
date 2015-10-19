/*
 * framework/luahelper.c
 *
 * Copyright(c) 2007-2015 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <framework/luahelper.h>

const char * luahelper_get_strfield(lua_State * L, const char * key, const char * def)
{
	const char * value;

	lua_getfield(L, -1, key);
	value = luaL_optstring(L, -1, def);
	lua_pop(L, 1);

	return value;
}

lua_Number luahelper_get_numfield(lua_State * L, const char * key, lua_Number def)
{
	lua_Number value;

	lua_getfield(L, -1, key);
	value = luaL_optnumber(L, -1, def);
	lua_pop(L, 1);

	return value;
}

lua_Integer luahelper_get_intfield(lua_State * L, const char * key, lua_Integer def)
{
	lua_Integer value;

	lua_getfield(L, -1, key);
	value = luaL_optinteger(L, -1, def);
	lua_pop(L, 1);

	return value;
}

void luahelper_set_strfield(lua_State * L, const char * key, const char * value)
{
	lua_pushstring(L, value);
	lua_setfield(L, -2, key);
}

void luahelper_set_numfield(lua_State * L, const char * key, lua_Number value)
{
	lua_pushnumber(L, value);
	lua_setfield(L, -2, key);
}

void luahelper_set_intfield(lua_State * L, const char * key, lua_Integer value)
{
	lua_pushinteger(L, value);
	lua_setfield(L, -2, key);
}

void luahelper_preload(lua_State * L, const char * name, lua_CFunction f)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, f);
	lua_setfield(L, -2, name);
	lua_pop(L, 2);
}

void luahelper_create_metatable(lua_State * L, const char * name, const luaL_Reg * funcs)
{
	luaL_newmetatable(L, name);
	luaL_setfuncs(L, funcs, 0);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}
