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
#include "../pathfinder/pathfinder.hpp"
#include "wx/dir.h"
#include "../start.hpp"
#include "../maploader/map.hpp"


extern wxString azppath;
extern double azpmoney;
extern wxString azpname;
extern int vadrixchar;

AZPNewGame::AZPNewGame(const wxString& title) : wxDialog(NULL,wxID_ANY,title,wxDefaultPosition,wxDefaultSize,wxCAPTION|wxRESIZE_BORDER)
{
	SetSize(400,400);
	wxPanel* panel=new wxPanel(this);
	wxStaticText* tname=new wxStaticText(panel,wxID_ANY,_("Name: "),wxPoint(20,20),wxSize(100,20));
	name=new wxTextCtrl(panel,wxID_ANY,azpname,wxPoint(120,20),wxSize(200,25));

	wxStaticText* tapilevel=new wxStaticText(panel,wxID_ANY,_("API Level: "),wxPoint(20,70),wxSize(100,20));
	wxArrayString arrayLG;
	arrayLG.Add(_("JUNO"));
	//arrayLG.Add(_("LINK"));
	//arrayLG.Add(_("APOLLO"));
	apilevel=new wxChoice(panel,wxID_ANY,wxPoint(120,70),wxSize(200,25),arrayLG);

	wxStaticText* tcharacter=new wxStaticText(panel,wxID_ANY,_("Character: "),wxPoint(20,120),wxSize(100,20));
	wxArrayString charArray;
	charArray.Add(_("Vadrix"));
	charArray.Add(_("Anti-Vadrix"));
	charArray.Add(_("Wadrix"));
	charArray.Add(_("Vandraxa"));
	character=new wxChoice(panel,wxID_ANY,wxPoint(120,120),wxSize(200,25),charArray);

	//Load all maps avalible

	wxStaticText* tmapstart=new wxStaticText(panel,wxID_ANY,_("Map: "),wxPoint(20,170),wxSize(100,20));
	wxArrayString mapArray=GetMapsAvalibles();
	mapstart=new wxChoice(panel,wxID_ANY,wxPoint(120,170),wxSize(200,25),mapArray);

	/*autosave=new wxCheckBox(panel,wxID_ANY,_("Autosave"),wxPoint(20,170));
	autosave->SetValue(true); -- For  3.0 */

	wxButton* next=new wxButton(panel,wxID_ANY,_("Next"),wxPoint(20,220),wxSize(200,25));
	next->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AZPNewGame::SaveIt),NULL,this);


}
void AZPNewGame::SaveIt(wxCommandEvent& event)
{
	azpname=name->GetValue();
	vadrixchar=character->GetCurrentSelection();
	wxString info_xml=GetMapsAvalibles()[mapstart->GetCurrentSelection()];
	//Check if map is in the ROOT or in the HOME
	if(info_xml.BeforeLast('/').EndsWith(wxT(".azpazeta/maps")))
	{
	//In HOME
	AzpMount* mount=new AzpMount(info_xml);
	Start* frame=new Start(wxT("Azpazeta JUNO"),PathFinder::GetUserPath()+wxT("/.azpazeta")+mount->mainmap);
	frame->Show();
	}else{
	//In ROOT
	AzpMount* mount=new AzpMount(info_xml);
	Start* frame=new Start(wxT("Azpazeta JUNO"),azppath+mount->mainmap);
	frame->Show();
	}



	//SaveDialog (also Saver Class) (like Simutrans saver) AUTOSAVE- NEVER
	wxFileDialog* select=new wxFileDialog(NULL,wxT("Choose the place to save your data"),wxT(""),wxT(""),wxT("AZP Save Files (*.azp)|*.azp"),wxFD_SAVE);
	select->ShowModal();
	SaveFile* saver=new SaveFile(select->GetPath());
	saver->SaveAll();
	saver->LoadAll();
	//Set VARS
	//Connect with Server
	Destroy();
	
	

}
wxArrayString AZPNewGame::GetMapsAvalibles()
{
	wxArrayString dirList;
	wxString azphomestr=PathFinder::GetUserPath();
	//Checking maps at AZP_ROOT
	#ifdef WIN32
	wxDir azproot(azppath+wxT("\\maps"));
#else
	wxDir azproot(azppath+wxT("/maps"));
#endif
	wxString dirAddress = azproot.GetName();
		

        azproot.GetAllFiles(dirAddress, &dirList, wxEmptyString, wxDIR_DIRS | wxDIR_FILES);
	wxArrayString mapAvalibles;
	int count=0;
	for(count=0;count<dirList.GetCount();count++)
	{
#ifdef WIN32
		if(dirList[count].AfterLast('\\').Cmp(wxT("info.xml"))==0)
		{
			mapAvalibles.Add(dirList[count]);

		}
#else
		if(dirList[count].AfterLast('/').Cmp(wxT("info.xml"))==0)
		{
			mapAvalibles.Add(dirList[count]);

		}
#endif

	}
//Checking maps in Azpazeta

wxArrayString dirListHome;
 wxDir azphome(azphomestr+wxT("/.azpazeta/maps"));
 wxString dirHome = azphome.GetName();
        azproot.GetAllFiles(dirHome, &dirListHome, wxEmptyString, wxDIR_DIRS | wxDIR_FILES);
 for(count=0;count<dirListHome.GetCount();count++)
 {
#ifdef WIN32
  if(dirListHome[count].AfterLast('\\').Cmp(wxT("info.xml"))==0)
  {
   mapAvalibles.Add(dirListHome[count]);

  }
#else
  if(dirListHome[count].AfterLast('/').Cmp(wxT("info.xml"))==0)
  {
   mapAvalibles.Add(dirListHome[count]);

  }
#endif

 }

	return mapAvalibles;
}
