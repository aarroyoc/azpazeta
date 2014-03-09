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



#include "GL/glew.h"
#include "app.hpp"
#include "start.hpp"
#include "window/options.hpp"
#include "version.hpp"
#include "display/opengl/gl.hpp"
#include "azpscript/azpvm.hpp"
#include "pathfinder/pathfinder.hpp"
#include "wx/utils.h"

#include "wx/busyinfo.h"
#include "maploader/map.hpp"
#include "maploader/azpmap.hpp"
#include "start/startgui.hpp"
#include "sprite/sprite.hpp"
#include "log.hpp"

#include "wx/sstream.h"
#include "wx/protocol/http.h"
#include "wx/wfstream.h"

BEGIN_EVENT_TABLE(Start, wxFrame)
    EVT_MENU(Minimal_Quit,  Start::OnQuit)
    EVT_MENU(Minimal_About, Start::OnAbout)
    EVT_MENU(SEE_VERSION_MENU, Start::SeeVersion)
    EVT_MENU(SEE_OPTIONS, Start::SeeOptions)
    EVT_MENU(AZPAZETA_UPDATER, Start::Updater)
END_EVENT_TABLE()

extern wxString azppath;

Start::Start(const wxString& title, const wxString& mapuri)
       : wxFrame(NULL, wxID_ANY, title)
{
	//Splash Screen
	//wxInitAllImageHandlers();
	//AzpLog("[OK] Loaded all image handlers",4);
	
	//wxBusyInfo wait(_("Please wait, working on something stupid"));
#ifdef WIN32
	wxIcon azpicon(azppath+wxT("/media/azpazeta.ico"));
	SetIcon(azpicon);

#endif

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
    wxMenu* editMenu=new wxMenu();
    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _("&About...\tF1"), _("Show about dialog"));
    editMenu->Append(SEE_OPTIONS, _("&Settings"),_("Change game settings"));
    fileMenu->Append(AZPAZETA_UPDATER,_("Azpazeta &Updater"),_("Check for updates"));
    fileMenu->Append(Minimal_Quit, _("E&xit\tAlt-X"), _("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("&File"));
    menuBar->Append(editMenu, _("&Edit"));
    menuBar->Append(helpMenu, _("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
	AzpLog("[OK] Created menubar",4);
#endif // wxUSE_MENUS
	//FullScreen
    if(LoadINIOptions().general.fullScreen)
		ShowFullScreen(true);
	else
		SetSize(800,800);
	AzpLog("[OK] Applyed full screen settings",4);






//Use AZPGL - Implementation of AZP Graphics in OpenGL ES 2

	//AzpVM DONE Moved to App.cpp
	/*AZPVM* azpvm=new AZPVM(azppath+wxT("/scripts/Init.azps"),azpVM_TEST);
	AzpLog("[OK] Started AzpVM with Init Script",4);*/
	//AzpEvent DONE


	//AzpMount QUIT
	/*AzpMount* azpmount=new AzpMount(azppath+wxT("/maps/core/info.xml"));
	AzpLog("[OK] Loaded main map data",4);*/

	//AzpMap TODO - Esto es un test
	//AzpMap* map=new AzpMap(azppath+wxT("/maps/core/start.xml")); //azpmount->mainmap
	//AzpMapData mapdata=map->GetData();
	//wxMessageBox(mapdata.inside.tile[1][1]);

	//AzpGL TODO
	wxPanel* glpanel=new wxPanel(this,wxID_ANY,wxPoint(1,1),wxSize(500,500));
	wxBoxSizer* sizer=new wxBoxSizer(wxHORIZONTAL);
	AZPGL* azpgl=new AZPGL(glpanel, /*azppath+azpmount->mainmap*/mapuri);
	sizer->Add(azpgl,1,wxEXPAND);
	glpanel->SetSizer(sizer);
	glpanel->SetAutoLayout(true);
	AzpLog("[OK] Displayed AZPGL",4);


#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Azpazeta 2.1 Link"));
#endif // wxUSE_STATUSBAR


}
Start::~Start()
{
	
}

// event handlers

void Start::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void Start::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    Version::Display::About();
}
void Start::SeeVersion(wxCommandEvent& event)
{
	Version::Display::About();	
}
void Start::SeeOptions(wxCommandEvent& event)
{
	Options* options=new Options(_("Options"));
	options->ShowModal();
}
void Start::Updater(wxCommandEvent& event)
{
	//Only check the URL for the user
	int check=wxMessageBox(_("Do you want to visit the project page for new updates?"),_("Azpazeta Updater"),wxYES_NO|wxICON_QUESTION);
	if(check==wxYES)
	{
		wxLaunchDefaultBrowser(wxT("http://launchpad.net/azpazeta/+download"));

	}
	/*
	//Only for WIN32 and TAR.GZ. The reason is that Linux users must use her package managers
	#ifndef WIN32
	wxMessageBox(_("Linux user: You must use your package manager for better performance. Only Windows user should update from here"),_("Divel Network"),wxOK|wxICON_WARNING);
	#else
	int check=wxMessageBox(_("Do you want to search Azpazeta updates"),_("Divel Network"),wxYES_NO|wxICON_QUESTION);
	if(check!=wxYES)
		return;
	AZPOptions options=LoadOptions();
	wxString host=(options.net.DivelAppsURL).AfterFirst('/').AfterFirst('/');
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetHeader(_T("User Agent"),_T("wxHTTP/2.8 (")+wxGetOsDescription()+_T(") wxWidgets/2.8 AzpazetaUpdater/2.0"));
	get.SetTimeout(10);
	while (!get.Connect(host))  // only the server, no pages here yet ...
	    wxSleep(5);
	#ifdef WIN32
	wxInputStream *httpStream = get.GetInputStream(wxT("/updater?PRODUCT=AZPAZETA_WIN32&VERSION=2"));
	#endif
	if (get.GetError() == wxPROTO_NOERR)
	{
	    wxString res;
	    wxStringOutputStream out_stream(&res);
	    httpStream->Read(out_stream);
		wxMessageBox(res);
		if(res.StartsWith(wxT("[URL]"))==true)
		{
			wxString urlupdate=res.AfterFirst('{').BeforeLast('}');
			wxMessageBox(_("Update avalible. Click OK to download"));
			wxFileDialog* select=new wxFileDialog(NULL,wxT("Select the place to save the installer"),wxT(""),wxT(""),wxT("All files (*)|*"),wxFD_SAVE);
			select->ShowModal();
			wxString host2=urlupdate.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
			wxString subpage2=urlupdate.AfterFirst('/').AfterFirst('/').AfterFirst('/')+wxT("/");
			wxHTTP get2;
			get2.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
			get2.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

			// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
			while (!get2.Connect(host2))  // only the server, no pages here yet ...
			    wxSleep(5);
	 
			wxInputStream *httpStream2 = get2.GetInputStream(subpage2);

			if (get2.GetError() == wxPROTO_NOERR)
			{
				
				wxFileOutputStream out_stream(select->GetPath());
				httpStream2->Read(out_stream);
			
			}
		}
		else{
			wxMessageBox(_("Azpazeta is already updated"));

		}

	}
	#endif
*/
}
