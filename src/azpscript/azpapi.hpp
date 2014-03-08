/*  	Azpazeta - Sandbox strategy game
    	Copyright (C) 2013  Adrián Arroyo Calle
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/* AzpAPI - Library of functions for AzpVM */
#ifndef AZPAPI_HPP
#define AZPAPI_HPP
#include "lua.hpp"
#include "azpvm.hpp"
#include "wx/wx.h"
#include "../version.hpp"
#include "../pathfinder/pathfinder.hpp"
#include "../database/database.hpp"
#include "../window/startmission.hpp"
#include "../physics/battle.hpp"

/**
* @brief Start the AZPScript context
* @param Name The Name of the Script
* @param Author The Author name
* @param Version Version of the Script
* @return The Operating System and the Azpazeta Version
* @note This is the Lua description of the function
* @see azpConsole
*
*/

int azpInit(lua_State*);
int azpConsole(lua_State*);
int azpLogo(lua_State*);
int azpWait(lua_State*);
int azpMosaic(lua_State*);
int azpExecute(lua_State*);
int azpGet(lua_State*);
int azpSet(lua_State*);
int azpStartMission(lua_State*);
int azpFinishMission(lua_State*);
int azpDialog(lua_State*);
int azpQuestion(lua_State*);
int azpBattle(lua_State*);
int azpVersionCLI(lua_State*);
float azpVersion();
#endif
