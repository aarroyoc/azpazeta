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
#include "azpapi.hpp"

float azpVersion()
{
	return 1.0;
}

int azpConsole(lua_State* l)
{
	if(lua_gettop(l)==1){
		wxLogVerbose(wxString::FromUTF8(lua_tostring(l,lua_gettop(l))));
	}else{
		wxLogWarning(wxT("Bad arguments in the current AZPScript->azpConsole function"));
	}
	return 0;
}
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

int azpInit(lua_State* l)
{
	
	int argc = lua_gettop(l);
	std::string parameter[3];
    for(int i=0; i<argc; i++)
    {
 	parameter[i]=lua_tostring(l, lua_gettop(l));
        lua_pop(l, 1);
    }
	wxString wxparameter[3];
	wxparameter[0]=wxString::FromUTF8(parameter[0].c_str());
	wxparameter[1]=wxString::FromUTF8(parameter[1].c_str());
	wxparameter[2]=wxString::FromUTF8(parameter[2].c_str());
	wxString message=wxT("Running new AZPScript: Name->");
	message.Append(wxparameter[0]);
	message.Append(wxT(" Author->"));
	message.Append(wxparameter[1]);
	message.Append(wxT(" Version->"));
	message.Append(wxparameter[2]);
 	wxLogMessage(message);
    // push to the stack the multiple return values
	//lua_pushnumber(l, 1); //1=Developer 0=Non-Developer Non avalible
	lua_pushstring(l,wxGetOsDescription().mb_str());
	lua_pushstring(l,AZPAZETA_VERSION_STR);
	//std::cout << "[AZPVM] Call azpInit" << std::endl;
 
    // number of return values
    return 2;
}
