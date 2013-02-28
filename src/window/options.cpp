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
#include "../app.hpp"
#include "options.hpp"
#include "wx/notebook.h"
#include "wx/glcanvas.h"
#include "wx/utils.h"
#include "../xml/tinyxml.h"
#include "../version.hpp"




Options::Options(const wxString& title) : wxDialog(NULL, wxID_ANY, title)
{	
	//Create tabs
	SetSize(500,600);
	wxPanel* commonbutton=new wxPanel(this,wxID_ANY,wxPoint(1,501),wxSize(500,100));
	wxNotebook* tabs=new wxNotebook(this,wxID_ANY,wxPoint(1,1),wxSize(500,500));
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
	//General tab DONE 
	
	fullScreen=new wxCheckBox(general,wxID_ANY,_("Full Screen"),wxPoint(1,1));
	fullScreen->SetValue(options.general.fullScreen);
	developer=new wxCheckBox(general,wxID_ANY,_("Developer"),wxPoint(1,30));
	developer->SetValue(options.general.developer);
	divelMarketing=new wxCheckBox(general,wxID_ANY,_("Allow Divel Marketing"),wxPoint(1,60));
	divelMarketing->SetValue(options.general.divelMarketing);

	seeVersion=new wxButton(general,SEE_VERSION,_("See version"),wxPoint(1,90));
	goWebpage=new wxButton(general,GO_WEB,_("Go to website"),wxPoint(1,120));
	seeVersion->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Options::SeeVersion),NULL,this);
	goWebpage->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Options::LaunchWebSite));

	
	//AZPScript tab DONE

	onlyFromMarket=new wxCheckBox(azpscript,wxID_ANY,_("Only from Market"),wxPoint(1,1));
	onlyFromMarket->SetValue(options.azpscript.onlyFromMarket);
	
	wxStaticText* azpazetaMarketURL=new wxStaticText(azpscript,wxID_ANY,_("Azpazeta Market URL: "),wxPoint(1,30),wxSize(150,15));
	XazpazetaMarketURL=new wxTextCtrl(azpscript,wxID_ANY,options.azpscript.azpazetaMarketURL,wxPoint(160,30),wxSize(200,25));

	/*allowPayPal=new wxCheckBox(azpscript,wxID_ANY,_("Allow PayPal"),wxPoint(1,60),wxSize(200,25));
	allowPayPal->SetValue(options.azpscript.allowPayPal);*/


	//Net tab DONE
	wxStaticText* divelAppsUrl=new wxStaticText(net,wxID_ANY,wxT("Divel Apps URL: "),wxPoint(1,1),wxSize(150,15));
	XdivelAppsUrl=new wxTextCtrl(net,wxID_ANY,options.net.DivelAppsURL,wxPoint(160,1),wxSize(200,25));
	
	autoConnect=new wxCheckBox(net,wxID_ANY,_("Auto-Update"),wxPoint(1,30));
	autoConnect->SetValue(options.net.autoConnect);

	wxStaticText* divelNetwork=new wxStaticText(net,wxID_ANY,_("Divel Network Name: "),wxPoint(1,60),wxSize(150,15));
	XdivelNetwork=new wxTextCtrl(net,wxID_ANY,options.net.DivelNetworkName,wxPoint(160,60),wxSize(200,25));
	
	wxStaticText* googleplus=new wxStaticText(net,wxID_ANY,_("Google+ Profile: "),wxPoint(1,90),wxSize(150,15));
	Xgoogleplus=new wxTextCtrl(net,wxID_ANY,options.net.GooglePlus,wxPoint(160,90),wxSize(200,25));
	


	//OpenGL DONE
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    
	glPane = new BasicGLPane( (wxPanel*) opengl, args);
	sizer->Add(glPane, 1, wxEXPAND);
	
	opengl->SetSizer(sizer);
	opengl->SetAutoLayout(true);
	wxStaticText* opengl_view=new wxStaticText(opengl,wxID_ANY,_("If you see the square and the cube your computer supports OpenGL"),wxPoint(1,1));
	//Sound TODO
	

	//Splash the tabs
	tabs->AddPage(general,_("General"));
	
	tabs->AddPage(azpscript,_("AZPScript"));
	tabs->AddPage(net,_("Net"));
	tabs->AddPage(opengl,_("OpenGL"));
	tabs->Layout();
	//On Close Dialog Apply or not? DONE
	
	optOk=new wxButton(commonbutton,OK_OPTIONS,_("OK"),wxPoint(125,1),wxSize(120,75));
	optCancel=new wxButton(commonbutton,CANCEL_OPTIONS,_("Cancel"),wxPoint(500-125,1),wxSize(120,75));
	optOk->SetFocus();
	optOk->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Options::Ok),NULL,this);
	optCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(Options::Cancel),NULL,this);

	

}
void Options::SeeVersion(wxCommandEvent& event)
{
	//Create Version Class DONE
	this->Destroy();
	developer->GetValue() ? Version::Display::All() : Version::Display::About(); 
	
	
}
void Options::LaunchWebSite(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser(wxT("http://launchpad.net/azpazeta"));
}
void Options::OnClose(wxCloseEvent& event)
{
	wxMessageBox(_("Closing"));
}
void Options::Ok(wxCommandEvent& event)
{
	SaveData();
	Destroy();
}
void Options::Cancel(wxCommandEvent& event)
{
	Destroy();
}
void Options::SaveData()
{
	//Get the data and put it into the XML file DONE
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );
	TiXmlElement * azpazeta_options = new TiXmlElement( "azpazeta-options" );
	azpazeta_options->SetAttribute("version","1.0");
	doc.LinkEndChild( azpazeta_options );
	//General Tab DONE
	TiXmlElement* general_option=new TiXmlElement("option-tab");	
	general_option->SetAttribute("id","general");
	azpazeta_options->LinkEndChild(general_option);

	TiXmlElement* option[3];
	option[0]=new TiXmlElement("option");
	option[1]=new TiXmlElement("option");
	option[2]=new TiXmlElement("option");
	
	option[0]->SetAttribute("id","fullScreen");
	option[1]->SetAttribute("id","developer");	
	option[2]->SetAttribute("id","divelMarketing");	

	general_option->LinkEndChild(option[0]);
	general_option->LinkEndChild(option[1]);
	general_option->LinkEndChild(option[2]);

	TiXmlText* text[3];
	text[0]=new TiXmlText(fullScreen->GetValue() ? "1" : "0");
	text[1]=new TiXmlText(developer->GetValue() ? "1" : "0");
	text[2]=new TiXmlText(divelMarketing->GetValue() ? "1" : "0");
	
	option[0]->LinkEndChild(text[0]);
	option[1]->LinkEndChild(text[1]);
	option[2]->LinkEndChild(text[2]);
	

	//AZPScript Tab DONE
	TiXmlElement* azpscript_tab=new TiXmlElement("option-tab");
	azpscript_tab->SetAttribute("id","azpscript");
	azpazeta_options->LinkEndChild(azpscript_tab);
	
	TiXmlElement* azpscript_option[3];
	azpscript_option[0]=new TiXmlElement("option");
	azpscript_option[1]=new TiXmlElement("option");
	azpscript_option[2]=new TiXmlElement("option");

	azpscript_option[0]->SetAttribute("id","onlyFromMarket");
	azpscript_option[1]->SetAttribute("id","azpazetaMarketURL");
	azpscript_option[2]->SetAttribute("id","allowPayPal");

	azpscript_tab->LinkEndChild(azpscript_option[0]);
	azpscript_tab->LinkEndChild(azpscript_option[1]);
	azpscript_tab->LinkEndChild(azpscript_option[2]);

	TiXmlText* azpscript_text[3];
	azpscript_text[0]=new TiXmlText(onlyFromMarket->GetValue() ? "1" : "0");
	azpscript_text[1]=new TiXmlText(XazpazetaMarketURL->GetValue().mb_str());
	//azpscript_text[2]=new TiXmlText(allowPayPal->GetValue() ? "1" : "0");

	azpscript_option[0]->LinkEndChild(azpscript_text[0]);
	azpscript_option[1]->LinkEndChild(azpscript_text[1]);
	//azpscript_option[2]->LinkEndChild(azpscript_text[2]);
	

	
	//Net Tab DONE
	TiXmlElement* net_tab=new TiXmlElement("option-tab");
	net_tab->SetAttribute("id","net");
	azpazeta_options->LinkEndChild(net_tab);

	TiXmlElement* net_option[4];
	net_option[0]=new TiXmlElement("option");
	net_option[1]=new TiXmlElement("option");
	net_option[2]=new TiXmlElement("option");	
	net_option[3]=new TiXmlElement("option");

	net_option[0]->SetAttribute("id","autoConnect");
	net_option[1]->SetAttribute("id","divelAppsURL");
	net_option[2]->SetAttribute("id","google-plus");
	net_option[3]->SetAttribute("id","divel-network");

	net_tab->LinkEndChild(net_option[0]);
	net_tab->LinkEndChild(net_option[1]);
	net_tab->LinkEndChild(net_option[2]);
	net_tab->LinkEndChild(net_option[3]);

	TiXmlText* net_text[4];
	net_text[0]=new TiXmlText(autoConnect->GetValue() ? "1" : "0");
	net_text[1]=new TiXmlText(XdivelAppsUrl->GetValue().mb_str());
	net_text[2]=new TiXmlText(Xgoogleplus->GetValue().mb_str());
	net_text[3]=new TiXmlText(XdivelNetwork->GetValue().mb_str());

	net_option[0]->LinkEndChild(net_text[0]);
	net_option[1]->LinkEndChild(net_text[1]);
	net_option[2]->LinkEndChild(net_text[2]);
	net_option[3]->LinkEndChild(net_text[3]);
	//Saving file DONE
	
	#ifdef WIN32
	const char* mihome="APPDATA";

	#else
	const char* mihome="HOME";

	#endif
	
	char* subPath=getenv(mihome);
	char localPath[1024];
	strcpy(localPath,subPath);
	strcat(subPath,"/.azpazeta/options.xml");
	doc.SaveFile(subPath);
}
