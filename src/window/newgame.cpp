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

#include "wx/wx.h"
#include "../savefile/savefile.hpp"
#include "newgame.hpp"

AZPNewGame::AZPNewGame() : wxDialog(NULL,wxID_ANY,_("New game"))
{
	SetSize(400,400);
	wxPanel* panel=new wxPanel(this);
	wxStaticText* tname=new wxStaticText(panel,wxID_ANY,_("Name: "),wxPoint(20,20),wxSize(100,20));
	name=new wxTextCtrl(panel,wxID_ANY,_("Vadrix"),wxPoint(120,20),wxSize(200,25));

	wxStaticText* tapilevel=new wxStaticText(panel,wxID_ANY,_("API Level: "),wxPoint(20,70),wxSize(100,20));
	wxArrayString arrayLG;
	arrayLG.Add(_("JUNO"));
	//arrayLG.Add(_("LINK"));
	//arrayLG.Add(_("APOLLO"));
	apilevel=new wxChoice(panel,wxID_ANY,wxPoint(120,50),wxSize(200,25),arrayLG);

	wxStaticText* tcharacter=new wxStaticText(panel,wxID_ANY,_("Character: "),wxPoint(20,120),wxSize(100,20));
	wxArrayString charArray;
	charArray.Add(_("Vadrix"));
	charArray.Add(_("Anti-Vadrix"));
	charArray.Add(_("Wadrix"));
	charArray.Add(_("Vandraxa"));
	apilevel=new wxChoice(panel,wxID_ANY,wxPoint(120,120),wxSize(200,25),charArray);

	autosave=new wxCheckBox(panel,wxID_ANY,_("Autosave"),wxPoint(20,170));
	autosave->SetValue(true);

	wxButton* next=new wxButton(panel,wxID_ANY,_("Next"),wxPoint(20,220),wxSize(200,25));
	next->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AZPNewGame::SaveIt),NULL,this);


}
void AZPNewGame::SaveIt(wxCommandEvent& event)
{
	//SaveDialog (also Saver Class) (like Simutrans saver)
	wxFileDialog* select=new wxFileDialog(NULL,wxT("Choose the place to save your progress"),wxT(""),wxT(""),wxT("AZP Save Files (*.azp)|*.azp"),wxFD_SAVE);
	select->ShowModal();
	wxMessageBox(wxT("Saving"));
	SaveFile* saver=new SaveFile(select->GetPath());
	
	//Connect with Server
	Destroy();
	
	

}
