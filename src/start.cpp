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

#include "app.hpp"
#include "start.hpp"
#include "window/options.hpp"
#include "version.hpp"
#include "display/opengl/gl.hpp"

BEGIN_EVENT_TABLE(Start, wxFrame)
    EVT_MENU(Minimal_Quit,  Start::OnQuit)
    EVT_MENU(Minimal_About, Start::OnAbout)
    EVT_MENU(SEE_VERSION_MENU, Start::SeeVersion)
    EVT_MENU(SEE_OPTIONS, Start::SeeOptions)
END_EVENT_TABLE()

Start::Start(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{

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
	wxPanel* glpanel=new wxPanel(this);
	AZPGL* azpgl=new AZPGL(glpanel);



#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR
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
