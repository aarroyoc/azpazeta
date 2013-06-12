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

#include "battle.hpp"

//Quiere decir que cada frase corresponde correctamente con el ID asignado
wxString question[]={
	_("You can say that the triangle has got 4 corners because you\n haven't studied geometry"), //0 
	_("You can't demostrate that god exists, so god doesn't exist"), //1
	_("That film it's good because the a lot of people have seen \nthe movie"), //2
	_("You must have graded my exam incorrectly. I studied very \nhard for weeks specifically because I knew my career depended on getting a good grade. If you give me a failing grade I'm ruined!"), //3
	_("Since 2000 the climate change advanced and the pirates \ndecreases, with less prirates we've got more climate change"), //4
	_("The root square of 2 is irrational, because Euclides say that"), //5
	_("I repeat it again, we will destroy the city of Orwell"), //6
	_("STOP stupid. I say that we need to draw a circle in the forest"), //7
	_("You aren't the best person for say this"), //0
	_("You can't demostrate that my son has gone to this party, \nso my son hasn't gone to this party"), //1
	_("Some virus are from the Azpazeta Spy Council,\n the people say that"), //2
	_("Ladies and gentlemen of the jury, look at this miserable man,\n in a wheelchair, unable to use his legs. Could such a man really be guilty of embezzlement?"), //3
	_("Sleeping with one's shoes on is strongly correlated with waking\n up with a headache, so sleeping with one's shoes on causes headache"), //4
	_("The earth has gravity, because Newton say that"), //5
	_("I say this about 1000 but one more time, I am inocent"), //6
	_("Silly boy, you need to get married with my sister")}; //7
AzpBattle::AzpBattle(wxString title, wxString user1, wxString user2, int type,long max) : wxDialog(NULL,wxID_ANY,wxT(""))
{

	Win=false;
	SetSize(800,600);
	SetTitle(_("Battle: ")+title+_(" - ")+user1+_(" VS ")+user2);
	wxPanel* left=new wxPanel(this,wxID_ANY,wxPoint(0,0),wxSize(400,300));
	wxPanel* right=new wxPanel(this,wxID_ANY,wxPoint(400,0),wxSize(400,300));
	wxPanel* down=new wxPanel(this,wxID_ANY,wxPoint(0,300),wxSize(800,300));
	current_points=100;
	max_pr=max;
	wxStaticText* user1_txt=new wxStaticText(left,wxID_ANY,user1,wxPoint(0,0));
	wxStaticText* user2_txt=new wxStaticText(right,wxID_ANY,user2,wxPoint(0,0));
	user1_status=new wxStaticText(left,wxID_ANY,wxT(""),wxPoint(5,25));
	user2_status=new wxStaticText(right,wxID_ANY,wxT(""),wxPoint(5,25));
	wxFont fuente=user1_txt->GetFont();
	fuente.SetWeight( wxBOLD );
	user1_txt->SetFont(fuente);
	user2_txt->SetFont(fuente);
	statusbar=new wxStaticText(down,wxID_ANY,wxT(""),wxPoint(0,0));
	if(type==0)
	{
		statusbar->SetLabel(_("Welcome to a philosophical battle"));
		action[0]=new wxButton(down,wxID_ANY,_("Ad hominen"),wxPoint(0,25)); //Desacreditar por la persona que es y no por la idea
		action[0]->Enable(false);
		action[0]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent0),NULL,this);
		action[1]=new wxButton(down,wxID_ANY,_("Ad ignorantiam"),wxPoint(0,50)); //Consiste en defender la verdad o falsedad de un enunciado basándose en la idea de que nadie ha probado lo contrario
		action[1]->Enable(false);
		action[1]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent1),NULL,this);
		action[2]=new wxButton(down,wxID_ANY,_("Ad populum"),wxPoint(150,25)); //Hacerse pasar por la opinión de la mayoría, aun sin ser cierto o la opinión de la mayoría está equivocada
		action[2]->Enable(false);
		action[2]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent2),NULL,this);
		action[3]=new wxButton(down,wxID_ANY,_("Ad misericordiam"),wxPoint(150,50));//se recurre a los sentimientos
		action[3]->Enable(false);
		action[3]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent3),NULL,this);
		action[4]=new wxButton(down,wxID_ANY,_("Cum hoc, ergo propter hoc"),wxPoint(300,25)); //con esto, luego a causa de esto, supone que dos hechos que ocurren juntos son uno causa del otro
		action[4]->Enable(false);
		action[4]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent4),NULL,this);
		action[5]=new wxButton(down,wxID_ANY,_("Ad verecundiam"),wxPoint(300,50)); //Por alguien lo ha dicho tiene que ser verdad
		action[5]->Enable(false);
		action[5]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent5),NULL,this);
		action[6]=new wxButton(down,wxID_ANY,_("Ad nauseam"),wxPoint(450,25));//una mentira repetida mil veces se transforma en realidad
		action[6]->Enable(false);
		action[6]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent6),NULL,this);
		action[7]=new wxButton(down,wxID_ANY,_("Ad baculum"),wxPoint(450,50)); //Uso de amenazas
		action[7]->Enable(false);
		action[7]->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AzpBattle::ClickEvent7),NULL,this);
		//More: http://manuelgross.bligoo.com/content/view/1127761/Las-10-reglas-de-la-argumentacion-y-13-tipos-de-falacias-argumentativas.html

		//Start battle, IA turn
		IATurn();





	}

}
void AzpBattle::ClickEvent0(wxCommandEvent& event)
{
	CheckAnswer(0);
}
void AzpBattle::ClickEvent1(wxCommandEvent& event)
{
	CheckAnswer(1);
}
void AzpBattle::ClickEvent2(wxCommandEvent& event)
{
	CheckAnswer(2);
}
void AzpBattle::ClickEvent3(wxCommandEvent& event)
{
	CheckAnswer(3);
}
void AzpBattle::ClickEvent4(wxCommandEvent& event)
{
	CheckAnswer(4);
}
void AzpBattle::ClickEvent5(wxCommandEvent& event)
{
	CheckAnswer(5);
}
void AzpBattle::ClickEvent6(wxCommandEvent& event)
{
	CheckAnswer(6);
}
void AzpBattle::ClickEvent7(wxCommandEvent& event)
{
	CheckAnswer(7);
}
bool AzpBattle::CheckAnswer(int response_id)
{
	//wxMessageBox(wxT("Checking answer"));
	if(response_id==question_id || response_id+8==question_id)
	{
		//GOOD
		statusbar->SetLabel(_("Good!"));
		int count;
		for(count=0;count<8;count++)
			action[count]->Enable(true);
		current_points+=100;
		if(current_points>=max_pr)
		{
			//You win the battle
			Win=true;
			this->Destroy();
			
		}else{
			IATurn();
		}
		
		
	}else{
		//BAD
		statusbar->SetLabel(_("Bad!"));
		int count;
		for(count=0;count<8;count++)
			action[count]->Enable(true);
		current_points-=100;
		if(current_points<0)
		{
			//You lose the battle
			Win=false;
			this->Destroy();
		}else{
			IATurn();
		}

	}
	

}
void AzpBattle::IATurn()
{
	srand(time(NULL));
	int random=rand()%16+1;
	//Hay 16 preguntas, dos para cada tipo
	user2_status->SetLabel(user2_status->GetLabel()+_("\n")+question[random]);
	question_id=random;
	int count;
	for(count=0;count<8;count++)
		action[count]->Enable(true);
	statusbar->SetLabel(_("Select the type of fallacy"));
}
