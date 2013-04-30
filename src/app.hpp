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
/**
@file app.hpp
@brief Entry point of Azpazeta
*/
#include "wx/wx.h"
#include "wx/intl.h"
#include "wx/cmdline.h"
#include "core/core.hpp"

#include "window/options.hpp" 
#ifndef APP_HPP
#define APP_HPP

typedef struct{			//Options structure
	struct net{		//Net options
			wxString DivelAppsURL; 
			bool autoConnect;
			wxString lastCheck;
			wxString GooglePlus;
			wxString DivelNetworkName;
			wxString UserAgent;
			//Check new version
			//Apply
		}net;	
	struct general{
			long language;
			bool fullScreen;	
			bool developer;
			bool divelMarketing;
			//See Version Information
			//Go to webpage
		}general;
	struct azpscript{
			bool onlyFromMarket;
			wxString azpVersion;
			wxString azpazetaMarketURL;
			bool allowPayPal;
			//Go to Market
			//Manage addons
		}azpscript;
		//Ok, Cancel
}AZPOptions;
/**
@class Azpazeta
@brief Entry point of Azpazeta and common functions
*/
class Azpazeta : public wxApp
{
public:
	virtual bool OnInit();
	/*virtual void OnInitCmdLine(wxCmdLineParser& parser);
        virtual bool OnCmdLineParsed(wxCmdLineParser& parser);*/
private:
	bool InitWxLocale();
	void Notify();
};
/*static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
     { wxCMD_LINE_SWITCH, _("h"), _("help"), _("displays help on the command line parameters"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
        {wxCMD_LINE_PARAM, NULL, NULL,_("save file"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},

     { wxCMD_LINE_NONE }
};*/
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,
    SEE_VERSION_MENU,
    SEE_OPTIONS
};
AZPOptions LoadOptions();
#endif
