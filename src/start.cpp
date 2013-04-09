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
#include "wx/splash.h"
#include "maploader/map.hpp"
#include "maploader/azpmap.hpp"
#include "start/startgui.hpp"
#include "sprite/sprite.hpp"

BEGIN_EVENT_TABLE(Start, wxFrame)
    EVT_MENU(Minimal_Quit,  Start::OnQuit)
    EVT_MENU(Minimal_About, Start::OnAbout)
    EVT_MENU(SEE_VERSION_MENU, Start::SeeVersion)
    EVT_MENU(SEE_OPTIONS, Start::SeeOptions)
END_EVENT_TABLE()

extern wxString azppath;

Start::Start(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	//Splash Screen
	wxInitAllImageHandlers();
	wxBitmap bitmap;
  	if (bitmap.LoadFile(azppath+wxT("/media/azpazeta.png"), wxBITMAP_TYPE_PNG))
  	{
      		wxSplashScreen* splash = new wxSplashScreen(bitmap,wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,6000, NULL, -1, wxDefaultPosition, wxDefaultSize,wxSIMPLE_BORDER|wxSTAY_ON_TOP);
  }
  wxYield();


#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
    wxMenu* editMenu=new wxMenu();
    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _("&About...\tF1"), _("Show about dialog"));
    editMenu->Append(SEE_OPTIONS, _("&Settings"),_("Change game settings"));
    fileMenu->Append(Minimal_Quit, _("E&xit\tAlt-X"), _("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("&File"));
    menuBar->Append(editMenu, _("&Edit"));
    menuBar->Append(helpMenu, _("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS






//Use AZPGL - Implementation of AZP Graphics in OpenGL ES 2

	//AzpVM DONE
	AZPVM* azpvm=new AZPVM(azppath+wxT("/scripts/Init.azps"),azpVM_TEST);

	//AzpData TODO


	//AzpMount TODO
	AzpMount* azpmount=new AzpMount(azppath+wxT("/maps/core/mount.xml"));

	//AzpMap TODO - Esto es un test
	//AzpMap* map=new AzpMap(azppath+wxT("/maps/core/start.xml")); //azpmount->mainmap
	//AzpMapData mapdata=map->GetData();
	//wxMessageBox(mapdata.inside.tile[1][1]);

	//AzpGL TODO
	wxPanel* glpanel=new wxPanel(this,wxID_ANY,wxPoint(1,1),wxSize(500,500));
	wxBoxSizer* sizer=new wxBoxSizer(wxHORIZONTAL);
	AZPGL* azpgl=new AZPGL(glpanel, azppath+azpmount->mainmap);
	sizer->Add(azpgl,1,wxEXPAND);
	glpanel->SetSizer(sizer);
	glpanel->SetAutoLayout(true);


#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR
	//FullScreen
    if(LoadOptions().general.fullScreen)
		ShowFullScreen(true);
	else
		SetSize(800,800);


}


// event handlers

void Start::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void Start::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    Version::Display::About();
}
void Start::SeeVersion(wxCommandEvent& event)
{
	//See Version dialog DONE
	Version::Display::About();
	
}
void Start::SeeOptions(wxCommandEvent& event)
{
	Options* options=new Options(_("Options"));
	options->ShowModal();

}
