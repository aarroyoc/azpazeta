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

#include "startmission.hpp"

extern bool azpmission;

AzpStartMission::AzpStartMission(wxString missionname,wxString missiondesc, unsigned short difficult, wxString scriptexec) : wxDialog (NULL,wxID_ANY,_("Start Mission"))
{
	scriptfile=scriptexec;
	SetSize(400,600);
	SetTitle(_("Start Mission - ")+missionname);

	wxPanel* panel=new wxPanel(this);
	
	wxStaticText* title=new wxStaticText(panel,wxID_ANY,missionname,wxPoint(0,0),wxSize(400,100));
	wxFont fuente=title->GetFont();
	fuente.SetWeight( wxBOLD );
	title->SetFont(fuente);

	wxStaticText* description=new wxStaticText(panel,wxID_ANY,missiondesc,wxPoint(0,100),wxSize(400,400));

	wxButton* ok=new wxButton(panel,wxID_ANY,_("Accept"),wxPoint(100,500),wxSize(100,50));
	ok->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpStartMission::ExecInitScript),NULL,this);
	wxButton* cancel=new wxButton(panel,wxID_ANY,_("Cancel"),wxPoint(200,500),wxSize(100,50));
	cancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpStartMission::AutoDestroy),NULL,this);



}
void AzpStartMission::ExecInitScript(wxCommandEvent& event)
{
	AZPVM* azpvm=new AZPVM(scriptfile,azpVM_SECURE);
	azpmission=true;
	Destroy();
}
void AzpStartMission::AutoDestroy(wxCommandEvent& event)
{
	Destroy();
}
