/*  Azpazeta - Sandbox strategy game
    Copyright (C) 2013  Adrián Arroyo Calle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "app.hpp"
#include "start.hpp"

IMPLEMENT_APP(Azpazeta)

bool Azpazeta::OnInit()
{
    // create the main application window
    //Init wxLocale funcionality
    if(!InitWxLocale())
	{
		wxMessageBox(_("Your language doesn't appear in Azpazeta translations. Please, create a translation in translations.launchpad.net/azpazeta"));
	}




    Start *frame = new Start(_("Minimal wxWidgets App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

wxLocale* locale;
long userLanguage;

bool Azpazeta::InitWxLocale()
{
	userLanguage=wxLANGUAGE_DEFAULT;
	 if(wxLocale::IsAvailable(userLanguage))
    	{
        	locale = new wxLocale( userLanguage, wxLOCALE_CONV_ENCODING );
 

        // add locale search paths

        locale->AddCatalogLookupPathPrefix(wxT("./lang"));


 
        locale->AddCatalog(wxT("azpazeta"));
 
        if(! locale->IsOk() )
        {
            locale = new wxLocale( wxLANGUAGE_ENGLISH );
            userLanguage = wxLANGUAGE_ENGLISH;
		return false;
        }
    	}
    	else
    	{
        	locale = new wxLocale( wxLANGUAGE_ENGLISH );
        	userLanguage = wxLANGUAGE_ENGLISH;
		return false;
    	}
	return true;
}
