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
#include "../app.hpp"
enum{
	CHECK_NEW_VERSION,
	APPLY_OPTIONS,
	OK_OPTIONS,
	CANCEL_OPTIONS,
	SEE_VERSION,
	GO_WEB,
	GO_MARKET,
	MANAGE_MAPS

};
class Options : public wxFrame
{
public:
	Options(const wxString& title); //Constructor
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
			int language;
			bool fullScreen;	
			bool developer;
			bool divelMarketing;
			//See Version Information
			//Go to webpage
		}general;
		struct azpscript{
			bool onlyFromMarket;
			wxString azpVersion;
			//Go to Market
			//Manage addons
		}azpscript;
		//Ok, Cancel
	}AZPOptions;
private:
	void Apply(wxCommandEvent& event);
	void Cancel(wxCommandEvent& event);
	void Ok(wxCommandEvent& event);
	void Tab(wxCommandEvent& event);
	DECLARE_EVENTS_TABLE()


};
