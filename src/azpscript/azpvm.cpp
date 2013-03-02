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
/* AzpVM - Azpazeta Virtual Machine */
#include "azpvm.hpp"
#include <iostream>
#include "wx/utils.h"
#include "../version.hpp"

AZPVM::AZPVM(wxString file, AZPVMState state)
{
	//Check files and state DONE
	wxLogMessage(wxT("AZPVM Running"));	//Debug TODO
	if(!wxFileExists(file))
	{
		wxLogError(wxT("The file doesn't exist. Reinstall the game can solve the problem"));
		return;
	}else{
		if(state==azpVM_TEST)wxLogVerbose(wxT("[AZPVM] Init AZPVM"));
		//Run 5.1 or 5.2
	


	}

}
static int azpInit(lua_State* l)
{
	wxLogMessage(wxT("Call azpInit"));
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
 	wxMessageBox(message);
    // push to the stack the multiple return values
	//lua_pushnumber(l, 1); //1=Developer 0=Non-Developer Non avalible
	lua_pushstring(l,wxGetOsDescription().mb_str());
	lua_pushstring(l,AZPAZETA_VERSION_STR);
 
    // number of return values
    return 2;
}
