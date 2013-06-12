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


class AzpBattle : public wxDialog
{
public:
	AzpBattle(wxString title, wxString user1, wxString user2, int type,long max);
	bool Win;
private:
	void ClickEvent0(wxCommandEvent& event);
	void ClickEvent1(wxCommandEvent& event);
	void ClickEvent2(wxCommandEvent& event);
	void ClickEvent3(wxCommandEvent& event);
	void ClickEvent4(wxCommandEvent& event);
	void ClickEvent5(wxCommandEvent& event);
	void ClickEvent6(wxCommandEvent& event);
	void ClickEvent7(wxCommandEvent& event);
	bool CheckAnswer(int response_id);
	void IATurn();
	wxString user1_pr;
	wxString user2_pr;
	long max_pr;
	wxStaticText* statusbar;
	wxButton* action[8];
	long current_points;
	wxStaticText* user1_status;
	wxStaticText* user2_status;
	int question_id;
	//wxString question[16]; //7
	

};
//Types of battle
//0->Philosophical
//1->Unimplemented ( like Final Fantasy)
//2->Humoristic (Uninpmeneted)
