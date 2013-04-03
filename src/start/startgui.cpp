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
#include "../window/options.hpp"
#include "startgui.hpp"
#include "wx/bmpbuttn.h"
#include "wx/wx.h"
#include "wx/sstream.h"
#include "wx/protocol/http.h"
#include "../version.hpp"
#include "wx/clipbrd.h"
#include "../azpmarket/azpmarket.hpp"
#include "../app.hpp"
#include "../core/core.hpp"


extern wxString azppath;
extern AzpClient* client;

StartDialog::StartDialog() : wxDialog (NULL,wxID_ANY,_("Azpazeta 2.0 Juno"),wxDefaultPosition,wxDefaultSize,wxCAPTION|wxMINIMIZE_BOX|wxSTAY_ON_TOP)
{
	SetSize(64*5,64*10);
	//Load bitmaps DONE
	wxImage azpazetaimg(azppath+wxT("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	wxBitmap azpscale=wxBitmap(azpazetaimg.Scale(64,64));

	wxBitmap singleplayer(azppath+wxT("/media/singleplayer.png"),wxBITMAP_TYPE_PNG); //Un jugador
	wxBitmap loadgame(azppath+wxT("/media/loadgame.png"),wxBITMAP_TYPE_PNG);
	wxBitmap multiplayer(azppath+wxT("/media/multiplayer.png"),wxBITMAP_TYPE_PNG);
	wxBitmap manager(azppath+wxT("/media/mapmanager.png"),wxBITMAP_TYPE_PNG);
	wxBitmap market(azppath+wxT("/media/azpmarket.png"),wxBITMAP_TYPE_PNG);
	wxBitmap options(azppath+wxT("/media/options.png"),wxBITMAP_TYPE_PNG);
	wxBitmap donate(azppath+wxT("/media/donate.png"),wxBITMAP_TYPE_PNG);


	//Put the DATA DONE
	wxPanel* panel=new wxPanel(this);

	/*wxBitmapButton* azpicon=new wxBitmapButton(panel,wxID_ANY,azpscale,wxPoint(64*2,1),wxSize(60,60));
	azpicon->SetBitmapSelected(azpscale);	
	azpicon->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::Version),NULL,this);*/

	wxStaticText* info=new wxStaticText(panel,wxID_ANY,_("Welcome to Azpazeta 2.0 Juno, the strategy-economic\n game in sandbox mode. Please select an option"),wxPoint(1,1));

	wxBitmapButton* newgame=new wxBitmapButton(panel,wxID_ANY,singleplayer,wxPoint(64,64));
	newgame->SetBitmapSelected(azpscale);
	newgame->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::NewGame),NULL,this);

	wxBitmapButton* loadGame=new wxBitmapButton(panel,wxID_ANY,loadgame,wxPoint(64*3,64));
	loadGame->SetBitmapSelected(azpscale);
	loadGame->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::LoadGame),NULL,this);

	wxBitmapButton* multiPlayer=new wxBitmapButton(panel,wxID_ANY,multiplayer,wxPoint(64,64*3));
	multiPlayer->SetBitmapSelected(azpscale);
	multiPlayer->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::Multiplayer),NULL,this);

	//Manager
	wxBitmapButton* Manager=new wxBitmapButton(panel,wxID_ANY,manager,wxPoint(64*3,64*3));
	Manager->SetBitmapSelected(azpscale);
	Manager->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::MapManager),NULL,this);


	//Market
	wxBitmapButton* Market=new wxBitmapButton(panel,wxID_ANY,market,wxPoint(64,64*5));
	Market->SetBitmapSelected(azpscale);
	Market->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::MapMarket),NULL,this);


	//Options
	wxBitmapButton* Options=new wxBitmapButton(panel,wxID_ANY,options,wxPoint(64*3,64*5));
	Options->SetBitmapSelected(azpscale);
	Options->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::Options2),NULL,this);

	//Donate
	wxBitmapButton* Donate=new wxBitmapButton(panel,wxID_ANY,donate,wxPoint(64,64*7));
	Donate->SetBitmapSelected(azpscale);
	Donate->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::Donate),NULL,this);

	//Version
	wxBitmapButton* version=new wxBitmapButton(panel,wxID_ANY,azpscale,wxPoint(64*3,64*7));
	version->SetBitmapSelected(azpscale);
	version->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(StartDialog::Version),NULL,this);


}
void StartDialog::NewGame(wxCommandEvent& event)
{
	client=new AzpClient(); //single player, localhost, ipv6 (WinXP users, sorry)
	client->Connect();
	//client->Disconnect();
	Destroy();
}
void StartDialog::LoadGame(wxCommandEvent& event)
{
	client=new AzpClient(azpCLIENT_LOAD);
	client->Connect();
	//client->Disconnect();
	Destroy();
}
void StartDialog::Multiplayer(wxCommandEvent& event)
{
	bool ipv6;
	//Find servers?
	int findserver=wxMessageBox(_("Do you want to find a server in Trola/Divel Network?"),_("Trola/Divel Network services"),wxYES_NO);
	if(findserver==wxYES)
		wxLaunchDefaultBrowser(wxT("http://sites.google.com/site/azpazeta/trola")); //Change for Divel Apps TODO
	//Type of IP
	wxArrayString typesofip;
	typesofip.Add(wxT("IPv4"));
	typesofip.Add(wxT("IPv6"));
	wxString typeip=wxGetSingleChoice(_("Select the type of protocol: "),_("Divel Network"),typesofip);
	if(typeip.Cmp(wxT("IPv6"))==0)
		ipv6=true;
	else
		ipv6=false;
	//IP
	wxString ip=wxGetTextFromUser(_("Insert the IP of the server"),_("Divel Network"),wxT(""));
	//Connect
	client=new AzpClient(azpCLIENT_MULTI,ip,ipv6);
	client->Connect();
	//client->Disconnect();
	Destroy();
}
void StartDialog::Version(wxCommandEvent& event)
{
	Version::Display::About();
}
void StartDialog::MapManager(wxCommandEvent& event)
{
	wxMessageBox(_("Map manager is not implemented in Juno. If you want to use another solution, try Trola, a pay app in Java"));
}
void StartDialog::MapMarket(wxCommandEvent& event)
{
	HTMLMarket* market=new HTMLMarket();
	market->ShowModal();
}
void StartDialog::Donate(wxCommandEvent& event)
{
	int clip=wxMessageBox(_("Do you want to spend some money on Azpazeta? We accept BitCoins and Bank Transfer. Divel BitCoins key is 1A2j8CwiFEhQ4Uycsjhr3gQPbJxFk1LRmM . Do you want to copy to the clipboard?"),_("Azpazeta Money"),wxYES_NO|wxICON_QUESTION);
	if(clip==wxYES)
	{
		if (wxTheClipboard->Open())
  		{
  		  // This data objects are held by the clipboard, 
  		  // so do not delete them in the app.
  		  wxTheClipboard->SetData( new wxTextDataObject(wxT("1A2j8CwiFEhQ4Uycsjhr3gQPbJxFk1LRmM")) );
  		  wxTheClipboard->Close();
  		}
	}
}
void StartDialog::Options2(wxCommandEvent& event)
{
	Options* options=new Options(_("Options"));
	options->ShowModal();
}
