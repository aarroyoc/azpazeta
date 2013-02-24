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
#include "options.hpp"
#include "wx/notebook.h"
#include "wx/glcanvas.h"




Options::Options(const wxString& title) : wxDialog(NULL, wxID_ANY, title)
{	
	//Create tabs
	SetSize(500,600);
	wxPanel* commonbutton=new wxPanel(this,wxID_ANY,wxPoint(1,501),wxSize(500,100));
	wxNotebook* tabs=new wxNotebook(this,wxID_ANY,wxPoint(1,1),wxSize(500,500));
	wxPanel* general=new wxPanel(tabs);
	wxPanel* azpscript=new wxPanel(tabs);
	wxPanel* net=new wxPanel(tabs);
	wxPanel* opengl=new wxPanel(tabs);
	//Adding controls to the tabs
	//General tab
	wxArrayString arrayLG;
	arrayLG.Add(_("English"));
	arrayLG.Add(_("Spanish"));
	arrayLG.Add(_("French"));
	
	//getLanguage=new wxChoice(general,wxID_ANY,wxDefaultPosition,wxDefaultSize,arrayLG); Used default language



	//Loading data
	AZPOptions options=LoadOptions(); 
	//General tab TODO 
	
	fullScreen=new wxCheckBox(general,wxID_ANY,_("Full Screen"),wxPoint(1,1));
	fullScreen->SetValue(options.general.fullScreen);
	developer=new wxCheckBox(general,wxID_ANY,_("Developer"),wxPoint(1,30));
	developer->SetValue(options.general.developer);
	divelMarketing=new wxCheckBox(general,wxID_ANY,_("Allow Divel Marketing"),wxPoint(1,60));
	divelMarketing->SetValue(options.general.divelMarketing);

	seeVersion=new wxButton(general,SEE_VERSION,_("See version"),wxPoint(1,90));
	goWebpage=new wxButton(general,GO_WEB,_("Go to website"),wxPoint(1,120));
	seeVersion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Options::SeeVersion));

	
	//AZPScript tab TODO


	//Net tab TODO
	wxStaticText* divelAppsUrl=new wxStaticText(net,wxID_ANY,wxT("Divel Apps URL: "),wxPoint(1,1),wxSize(150,15));
	XdivelAppsUrl=new wxTextCtrl(net,wxID_ANY,options.net.DivelAppsURL,wxPoint(160,1),wxSize(200,25));
	
	autoConnect=new wxCheckBox(net,wxID_ANY,_("Auto-Update"),wxPoint(1,30));
	autoConnect->SetValue(options.net.autoConnect);
	


	//OpenGL DONE
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    
	glPane = new BasicGLPane( (wxPanel*) opengl, args);
	sizer->Add(glPane, 1, wxEXPAND);
	
	opengl->SetSizer(sizer);
	opengl->SetAutoLayout(true);
	wxStaticText* opengl_view=new wxStaticText(opengl,wxID_ANY,_("If you see the square and the cube your computer supports OpenGL"),wxPoint(1,1));
	//Sound TODO

	//Splash the tabs
	tabs->AddPage(general,_("General"));
	
	tabs->AddPage(azpscript,_("AZPScript"));
	tabs->AddPage(net,_("Net"));
	tabs->AddPage(opengl,_("OpenGL"));
	tabs->Layout();
	//On Close Dialog Apply or not? TODO

	

}
void Options::SeeVersion(wxCommandEvent& event)
{
	wxMessageBox(_("HI"));
}
void Options::OnClose(wxCloseEvent& event)
{
	wxMessageBox(_("Closing"));
}
