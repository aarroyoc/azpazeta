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

#include "longtalk.hpp"

LongTalk::LongTalk(wxString bitmapfile1, wxString bitmapfile2, wxArrayString dialogarray1,wxArrayString dialogarray2, int numberoftalks) : wxDialog (NULL,wxID_ANY,_("Dialog"),wxDefaultPosition,wxDefaultSize)
{
	max=numberoftalks;
	array1=dialogarray1;
	array2=dialogarray2;
	SetSize(800,800);
	wxPanel* main=new wxPanel(this);

	wxBitmap bitmap1(bitmapfile1,wxBITMAP_TYPE_PNG); //Image must be 400x200
	wxBitmap bitmap2(bitmapfile2,wxBITMAP_TYPE_PNG);

	wxStaticBitmap* xbitmap1=new wxStaticBitmap(main,wxID_ANY,bitmap1,wxPoint(0,0),wxSize(400,200));
	wxStaticBitmap* xbitmap2=new wxStaticBitmap(main,wxID_ANY,bitmap2,wxPoint(400,0),wxSize(400,200));
	
	if(numberoftalks>0)
	{
		dialog1=new wxStaticText(main,wxID_ANY,dialogarray1[0],wxPoint(0,400),wxSize(400,500));
		dialog2=new wxStaticText(main,wxID_ANY,dialogarray2[0],wxPoint(400,400),wxSize(400,500));
		current=0;
	
	}
	nextdialog=new wxButton(main,wxID_ANY,_("Next"),wxPoint(200,700),wxSize(200,100));
	nextdialog->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(LongTalk::NextDialog),NULL,this);
}
LongTalk::~LongTalk()
{
	delete dialog1;
	delete dialog2;
}
void LongTalk::NextDialog(wxCommandEvent& event)
{
	if(current<max)
	{	
		dialog1->SetLabel(array1[current]);
		dialog2->SetLabel(array2[current]);
		current++;
	}else{
		this->Destroy();
	}
}
