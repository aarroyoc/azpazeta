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

Options::Options(const wxString& title) : wxDialog(NULL, wxID_ANY, title)
{	
	//Create tabs
	wxNotebook* tabs=new wxNotebook(this,wxID_ANY);
	wxPanel* general=new wxPanel(tabs);
	wxPanel* azpscript=new wxPanel(tabs);
	wxPanel* net=new wxPanel(tabs);
	//Adding controls
	wxArrayString arrayLG;
	arrayLG.Add(_("English"));
	arrayLG.Add(_("Spanish"));
	arrayLG.Add(_("French"));
	
	getLanguage=new wxChoice(general,wxID_ANY,wxPoint(1,1),wxSize(200,20),arrayLG);

	//Splash the tabs
	tabs->AddPage(general,_("General"));
	tabs->AddPage(azpscript,_("AZPScript"));
	tabs->AddPage(net,_("Net"));
	tabs->Layout();

}

