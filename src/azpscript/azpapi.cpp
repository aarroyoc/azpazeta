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

/**
 * @file azpapi.cpp
 * @brief AzpAPI - Library of functions for AzpVM
 * @see AzpVM
 * @author Adrián Arroyo Calle
 */
#include "azpapi.hpp"
/**
 * @brief Get the current version of AZPScript
 * @returns The number of the version
 */
bool azplogo;
bool azpmosaic;
extern wxString azppath;

float azpVersion()
{
	return 1.0;
}
/**
 * @brief Show a string in the Window Console
 * @param l AzpVM instance
 * @returns Number of output values
 * @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
 * @see AzpAPI::azpConsole
 */
 
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
* @param l AzpVM instance
* @returns Number of output values
* @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
* @see AzpAPI::azpInit
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


	//Set default vars
	azplogo=false;
 
    // number of return values
    return 2;
}
/**
* @brief Display the Azpazeta logo
* @param l AzpVM instance
* @returns Number of output values
* @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
* @see AzpAPI::azpLogo
*
*/

int azpLogo(lua_State* l)
{

	azplogo=true;
	return 0;
}
/**
* @brief Wait the selected miliseconds
* @param l AzpVM instance
* @returns Number of output values
* @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
* @see AzpAPI::azpLogo
*
*/

int azpWait(lua_State* l)
{
	int argc = lua_gettop(l);
	long milliseconds=lua_tointeger(l, lua_gettop(l));
	wxMilliSleep(milliseconds);
	return 0;
}
/**
* @brief Display the Azpazeta Mosaic
* @param l AzpVM instance
* @returns Number of output values
* @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
* @see azpLogo
*
*/

int azpMosaic(lua_State* l)
{
	azpmosaic=true;
	return 0;
}
/**
* @brief Executes another instance of AzpVM
* @param l AzpVM instance
* @returns Number of output values
* @note This function is part of AzpAPI avalible trough AZPScript in AzpVM
* @see azpLogo
*
*/

int azpExecute(lua_State* l)
{
	AZPVMState levelstate=azpVM_SECURE;
	int argc = lua_gettop(l);
	lua_pop(l,1);
	std::string file=lua_tostring(l, lua_gettop(l));
	lua_pop(l, 1);
	std::string level=lua_tostring(l,lua_gettop(l));
	if(level.compare("azpVM_FULL")==0)
	{
		levelstate=azpVM_FULL;
	}
	if(level.compare("azpVM_SECURE")==0)
	{
		levelstate=azpVM_SECURE;
	}
	if(level.compare("azpVM_INSTALLATION")==0)
	{
		levelstate=azpVM_INSTALLATION;
	}
	if(level.compare("azpVM_TEST")==0)
	{
		levelstate=azpVM_TEST;
	}
	if(level.compare("azpVM_INTERNET")==0)
	{
		levelstate=azpVM_INTERNET;
	}
	AZPVM* azpvm=new AZPVM(azppath+wxString::FromUTF8(file.c_str()),levelstate);


	return 0;
}
