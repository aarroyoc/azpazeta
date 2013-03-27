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


extern wxString azppath;

StartDialog::StartDialog() : wxDialog (NULL,wxID_ANY,_("Azpazeta 2.0 Juno"))
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


	//Put the DATA TODO
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


 /*
wxHTTP get;
get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...
 
// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
while (!get.Connect(_T("www.google.com")))  // only the server, no pages here yet ...
    wxSleep(5);
 
wxApp::IsMainLoopRunning(); // should return true
 
// use _T("/") for index.html, index.php, default.asp, etc.
wxInputStream *httpStream = get.GetInputStream(_T("/intl/en/about.html"));
 
// wxLogVerbose( wxString(_T(" GetInputStream: ")) << get.GetResponse() << _T("-") << ((resStream)? _T("OK ") : _T("FAILURE ")) << get.GetError() );
 
if (get.GetError() == wxPROTO_NOERR)
{
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
 
    wxMessageBox(res);
    // wxLogVerbose( wxString(_T(" returned document length: ")) << res.Length() );
}
else
{
    wxMessageBox(_T("Unable to connect!"));
}
 
wxDELETE(httpStream);
get.Close();
*/

}
void StartDialog::NewGame(wxCommandEvent& event)
{

}
void StartDialog::LoadGame(wxCommandEvent& event)
{

}
void StartDialog::Multiplayer(wxCommandEvent& event)
{

}
void StartDialog::Version(wxCommandEvent& event)
{
	Version::Display::About();
}
void StartDialog::MapManager(wxCommandEvent& event)
{

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
