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
	SetSize(500,500);
	wxNotebook* tabs=new wxNotebook(this,wxID_ANY);
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
	/*
	fullScreen=new wxCheckBox();
	developer=new wxCheckBox();
	divelMarketing=new wxCheckBox();
	seeVersion=new wxButton();
	goWebpage=new wxButton();*/

	
	//AZPScript tab TODO


	//Net tab TODO
	wxStaticText* divelAppsUrl=new wxStaticText(net,wxID_ANY,wxT("Divel Apps URL: ")+options.net.DivelAppsURL,wxPoint(1,1),wxSize(490,15));
	
	autoConnect=new wxCheckBox(net,wxID_ANY,_("Auto-Update"),wxPoint(1,25));
	autoConnect->SetValue(options.net.autoConnect);
	


	//OpenGL
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    
	glPane = new BasicGLPane( (wxPanel*) opengl, args);
	sizer->Add(glPane, 1, wxEXPAND);
	
	opengl->SetSizer(sizer);
	opengl->SetAutoLayout(true);
	wxStaticText* opengl_view=new wxStaticText(opengl,wxID_ANY,_("If you see the square and the cube your computer supports OpenGL"),wxPoint(1,1));

	//Splash the tabs
	tabs->AddPage(general,_("General"));
	
	tabs->AddPage(azpscript,_("AZPScript"));
	tabs->AddPage(net,_("Net"));
	tabs->AddPage(opengl,_("OpenGL"));
	tabs->Layout();

}
