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

#include "app.hpp"
#include "start.hpp"
#include "./window/options.hpp"
#include "./pathfinder/pathfinder.hpp"
#include "wx/wx.h"
#include "start/startgui.hpp"
#include "wx/taskbar.h"
#include "log.hpp"
#include "wx/cmdline.h"
#include "wx/settings.h"
#include "wx/splash.h"
#include "azpscript/azpvm.hpp"
#include "savefile/savefile.hpp"
#include "window/newgame.hpp"
#include "network/telemetry.hpp"
#include "sound/sound.hpp"
#include "wx/fileconf.h"

#include "xml/tinyxml.h"

#include <config.h>

IMPLEMENT_APP(Azpazeta)

AzpClient* client;
extern wxString azppath;
int vadrixchar;
wxString azpname;
extern bool azpmission;
extern double azpmoney;

bool Azpazeta::OnInit()
{
	AzpLog("[INFO] Welcome to Azpazeta!",1);
	AzpLog("[INFO] Running Link version",1);

	SetAppName(wxT("Azpazeta"));
	SetVendorName(wxT("Adrián Arroyo Calle for Divel"));
	
	azpmission=false;
	azpmoney=1000.0;
	azpname=_("Vadrix");
	vadrixchar=0;
	bool loader=false;
	


	if(wxApp::argc>=2)
	{
		AzpLog("[INFO] Processing parameters",1);
		//AzpLog(wxString(wxApp::argv[1]).mb_str(),1);
		if(wxString(wxApp::argv[1]).Cmp(wxT("--help"))==0)
		{
			AzpLog("[INFO] Running help mode",1);
			AzpLog("Azpazeta 2.0 JUNO\nUsage:\n\tAZPAZETA_JUNO [--help]\n\tAZPAZETA_JUNO [savefile]\n\tAZPAZETA_JUNO [script]",1);
			return false;
		}else{
			AzpLog("[INFO] Running loader mode",1);
			loader=true;
		
		}	
	}else{
		AzpLog("[INFO] Running normal mode",1);
		wxSystemScreenType screentype=wxSystemSettings::GetScreenType();
		switch(screentype)
		{
			case wxSYS_SCREEN_NONE:AzpLog("[WARNING] Running in a undefined screen",2);break;
			case wxSYS_SCREEN_TINY:AzpLog("[WARNING] Tiny Screen (320x240). Some dialogues can appear incomplete",2);break;
			case wxSYS_SCREEN_PDA:AzpLog("[WARNING] PDA Screen. Some dialogues can appear incomplete",2);break;
			case wxSYS_SCREEN_SMALL:AzpLog("[WARNING] Small Screen. Some dialogues can appear incomplete",2);break;
			case wxSYS_SCREEN_DESKTOP:AzpLog("[OK] Desktop Screen. All dialogues appears fine",4);break;

		}	
		
	}
	
	
    // create the main application window
    //Init wxLocale funcionality
    if(!InitWxLocale())
	{
		wxMessageBox(_("Your language doesn't appear in Azpazeta translations. Please, create a translation in translations.launchpad.net/azpazeta"));
		AzpLog("[WARNING] This language doesn't appear in Azpazeta Translations",2);
	}
	AzpLog("[OK] Localization",4);

	//Get Installed path
	PathFinder::Start();
	AzpLog("[OK] PathFinder gets Azpazeta Resources Dir",4);
	Notify();
	wxInitAllImageHandlers();
	AzpLog("[OK] Loaded all image handlers",4);

	//TaskBar Icon
#ifdef WIN32
	wxIcon azpicon(azppath+wxT("/media/azpazeta.ico"),wxBITMAP_TYPE_ICO);
	/* System Tray Whitelist Ubuntu 12.04 & Ubuntu 12.10 */
	/* gsettings set com.canonical.Unity.Panel systray-whitelist "['all']" */
	wxTaskBarIcon* trayicon=new wxTaskBarIcon();
	trayicon->SetIcon(azpicon,_("Azpazeta Juno Running"));
	if(!trayicon->IsOk())
		AzpLog("[WARNING] Error creating TrayIcon",2);
	else
		AzpLog("[OK] Created TrayIcon",4);
#else
	wxBitmap azpimg(azppath+wxT("/media/azpazeta.png"));
	wxIcon azpicon;
	azpicon.CopyFromBitmap(azpimg);
	/* System Tray Whitelist Ubuntu 12.04 & Ubuntu 12.10 */
	/* gsettings set com.canonical.Unity.Panel systray-whitelist "['all']" */
	wxTaskBarIcon* trayicon=new wxTaskBarIcon();
	trayicon->SetIcon(azpicon,_("Azpazeta Juno Running"));
	if(!trayicon->IsOk())
		AzpLog("[WARNING] Error creating TrayIcon",2);
	else
		AzpLog("[OK] Created TrayIcon",4);
#endif

	/*Start *frame = new Start(_("Azpazeta Juno"));

	    // and show it (the frames, unlike simple controls, are not shown when
	    // created initially)
	frame->Show(true);*/
	//Start sound 
	#ifdef AZP_AUDIO
	AzpLog("[OK] Started audio thread",4);
	AZPAudio* audio=new AZPAudio((azppath+wxT("/media/music/ClassicRPGBattle.ogg")).mb_str());
	#endif
		//Start Dialog
	wxBitmap bitmap;
#ifdef WIN32
	wxString azpiconpath=wxT("\\media\\azpazeta.png");
#else
	wxString azpiconpath=wxT("/media/azpazeta.png");
#endif
  	if (bitmap.LoadFile(azppath+azpiconpath,wxBITMAP_TYPE_PNG))
  	{
      		wxSplashScreen* splash = new wxSplashScreen(bitmap,wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,6000, NULL, -1, wxDefaultPosition, wxDefaultSize,wxSIMPLE_BORDER|wxSTAY_ON_TOP);
		AzpLog("[OK] Display Splash Screen",4);
  }else{
	AzpLog("[ERROR] Azpazeta can't load $AZP_ROOT/media/azpazeta.png",3);
	wxExit();
	}
	//Run Divel Telemetry if required
	int lang=wxLocale::GetSystemLanguage();
	wxString lang_param;
	switch(lang)
	{
		case wxLANGUAGE_ARABIC:lang_param=wxT("ar");break;
		case wxLANGUAGE_CHINESE:lang_param=wxT("zh");break;
		case wxLANGUAGE_CROATIAN:lang_param=wxT("hr");break;
		case wxLANGUAGE_CZECH:lang_param=wxT("cs");break;	
		case wxLANGUAGE_DANISH:lang_param=wxT("da");break;
		case wxLANGUAGE_DUTCH:lang_param=wxT("nl");break;
		case wxLANGUAGE_ENGLISH:
		case wxLANGUAGE_ENGLISH_UK: 	
		case wxLANGUAGE_ENGLISH_US:lang_param=wxT("en");break;
		case wxLANGUAGE_ESPERANTO:lang_param=wxT("eo");break;
		case wxLANGUAGE_FRENCH:lang_param=wxT("fr");break;
		case wxLANGUAGE_GERMAN:lang_param=wxT("de");break;
		case wxLANGUAGE_ITALIAN:lang_param=wxT("it");break;
		case wxLANGUAGE_JAPANESE:lang_param=wxT("ja");break;
		case wxLANGUAGE_KOREAN:lang_param=wxT("ko");break;
		case wxLANGUAGE_LATIN:lang_param=wxT("la");break;
		case wxLANGUAGE_PORTUGUESE:	
		case wxLANGUAGE_PORTUGUESE_BRAZILIAN:lang_param=wxT("pt");break;
		case wxLANGUAGE_RUSSIAN:lang_param=wxT("ru");break;
		case wxLANGUAGE_SPANISH:
		case wxLANGUAGE_SPANISH_ARGENTINA :
		case wxLANGUAGE_SPANISH_BOLIVIA :	
		case wxLANGUAGE_SPANISH_CHILE 	:
		case wxLANGUAGE_SPANISH_COLOMBIA :	
		case wxLANGUAGE_SPANISH_COSTA_RICA: 	
		case wxLANGUAGE_SPANISH_DOMINICAN_REPUBLIC 	:
		case wxLANGUAGE_SPANISH_ECUADOR 	:
		case wxLANGUAGE_SPANISH_EL_SALVADOR 	:
		case wxLANGUAGE_SPANISH_GUATEMALA 	:
		case wxLANGUAGE_SPANISH_HONDURAS 	:
		case wxLANGUAGE_SPANISH_MEXICAN 	:
		case wxLANGUAGE_SPANISH_MODERN 	:
		case wxLANGUAGE_SPANISH_NICARAGUA: 	
		case wxLANGUAGE_SPANISH_PANAMA 	:
		case wxLANGUAGE_SPANISH_PARAGUAY :	
		case wxLANGUAGE_SPANISH_PERU 	:
		case wxLANGUAGE_SPANISH_PUERTO_RICO : 	
		case wxLANGUAGE_SPANISH_URUGUAY 	:
		case wxLANGUAGE_SPANISH_US 	:
		case wxLANGUAGE_SPANISH_VENEZUELA :lang_param=wxT("es"); break;
		default: lang_param=wxT("en");
	}
	
	wxString screen_string=wxString::Format(wxT("%dx%d"),wxSystemSettings::GetMetric ( wxSYS_SCREEN_X ),wxSystemSettings::GetMetric ( wxSYS_SCREEN_Y ) );
	#ifdef TELEMETRY
	if(LoadINIOptions().net.divelTelemetry)
	{
	
		//Telemetry AppStart
		Telemetry* telemetry=new Telemetry(wxT("UA-20035972-12"),wxT("Azpazeta"),wxT("2.0.0"),wxT("AppStart"),screen_string,lang_param);
		telemetry->Send();
		delete telemetry;
	}else{
		AzpLog("[INFO] Telemetry not enabled",1);
	}
	#endif
	//AZPVM
	AZPVM* azpvm=new AZPVM(azppath+wxT("/scripts/Init.azps"),azpVM_TEST);
	AzpLog("[OK] Started AzpVM with Init Script",4);
	//STARTDIALOG
	if(!loader)
	{
		StartDialog* stdg=new StartDialog();
		stdg->ShowModal();
	}else{
	//Copy from newgame.cpp
	SaveFile* saver=new SaveFile(wxApp::argv[1]);
	saver->LoadAll();

	//Change settings
	AZPNewGame* loadgame=new AZPNewGame(_("Load game"));
	loadgame->ShowModal();

	//Open SERVER
	client=new AzpClient(azpCLIENT_LOAD);
	client->Connect();
	//client->Disconnect();
	//Destroy();

	}

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
void Azpazeta::Notify()
{
	//Win32 TODO
	#ifdef WIN32

	//Linux-Ayatana DONE
	#else
	wxShell(wxT("notify-send -i azpazeta \"Azpazeta\" \"Welcome to Azpazeta 2.1 Link\""));

	#endif 


}
/*void Azpazeta::OnInitCmdLine(wxCmdLineParser& parser)
{
	wxMessageBox(_("Parsing"));
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool Azpazeta::OnCmdLineParsed(wxCmdLineParser& parser)
{
	wxMessageBox(_("Parsing"));
    //silent_mode = parser.Found(wxT("s"));
    // to get at your unnamed parameters use
    wxArrayString files;
        for (int i = 0; i < parser.GetParamCount(); i++)
    {
            files.Add(parser.GetParam(i));
    }

    // and other command line parameters
	wxMessageBox(files[0]);
	wxMessageBox(files[1]);
    // then do what you need with them.

    return true;
}*/
/**
 * @brief Loads options.xml file and returns a struct containing the options
 * @return AZPOptions struct with the user preferences
 * @note This function is deprecated and it's only for compatibility. You should use LoadINIOptions
 * @deprecated
 * @see LoadINIOptions
 * */
AZPOptions LoadOptions()
{
	//Cargar ficheros de opciones XML
	#ifdef WIN32
	const char* home="APPDATA";

	#else
	const char* home="HOME";

	#endif
	char* homePath=getenv(home);
	char localPath[1024];
	strcpy(localPath,homePath);
	strcat(localPath,"/.azpazeta/options.xml");
	AZPOptions options;
	//Usar TinyXML
	TiXmlDocument doc(localPath);
	if(!doc.LoadFile())
	{
		//Si no existe poner el guardado en carpeta de instalación
		wxCopyFile(PathFinder::GetInstalledPath()+wxT("/options/options.xml"),wxString::FromUTF8(localPath));
		return LoadOptions();
	}
	//Procesar XML
	//Obtener ROOT
	TiXmlElement *option_tab, *option;
	TiXmlElement* azpazeta_options=doc.RootElement();
	while (azpazeta_options) {
		//Parsear cada uno
		option_tab=azpazeta_options->FirstChildElement("option-tab");
		while(option_tab){ //Mientras haya OptionTab
			
			if(strcmp(option_tab->Attribute("id"),"general")==0){
				option=option_tab->FirstChildElement("option");
				//General Tab DONE
				while(option)
				{
					if(strcmp(option->Attribute("id"),"fullScreen")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.general.fullScreen=box;
					}				
					if(strcmp(option->Attribute("id"),"developer")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.general.developer=box;
					}
					if(strcmp(option->Attribute("id"),"divelMarketing")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.general.divelMarketing=box;
					}

					option=option->NextSiblingElement("option");
				}


			}
			if(strcmp(option_tab->Attribute("id"),"azpscript")==0){
				option=option_tab->FirstChildElement("option");
				//AZPScript Tab DONE
				while(option)
				{
					if(strcmp(option->Attribute("id"),"onlyFromMarket")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.azpscript.onlyFromMarket=box;
					}
					if(strcmp(option->Attribute("id"),"azpazetaMarketURL")==0){
						options.azpscript.azpazetaMarketURL=wxString::FromUTF8(option->GetText());
					}
					/*if(strcmp(option->Attribute("id"),"allowPayPal")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.azpscript.allowPayPal=box;
					}*/


					option=option->NextSiblingElement("option");
				}
				
			}
			if(strcmp(option_tab->Attribute("id"),"net")==0){
				option=option_tab->FirstChildElement("option");
				//Net Tab DONE
				while(option)
				{
					
					if(strcmp(option->Attribute("id"),"divelAppsURL")==0){
						wxString url=wxString::FromUTF8(option->GetText());
						options.net.DivelAppsURL=url;
					}
					if(strcmp(option->Attribute("id"),"autoConnect")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.net.autoConnect=box;
					}
					if(strcmp(option->Attribute("id"),"divelTelemetry")==0){
						bool box;
						if(strcmp(option->GetText(),"1")==0)
							box=true;
						else
							box=false;
						options.net.divelTelemetry=box;
					}
					if(strcmp(option->Attribute("id"),"google-plus")==0){
						options.net.GooglePlus=wxString::FromUTF8(option->GetText());
					}
					if(strcmp(option->Attribute("id"),"divel-network")==0){
						options.net.DivelNetworkName=wxString::FromUTF8(option->GetText());
					}
				
				//wxMessageBox(wxString::FromUTF8(option->Attribute("id")));
				option=option->NextSiblingElement("option");
				}
			}


		option_tab = option_tab->NextSiblingElement( "option-tab" );
		}

	azpazeta_options=azpazeta_options->NextSiblingElement("azpazeta-options");
	}


	return options; 
}

wxLocale* locale;
long userLanguage;

bool Azpazeta::InitWxLocale()
{
	userLanguage=wxLANGUAGE_DEFAULT;
	 if(wxLocale::IsAvailable(userLanguage))
    	{
        	locale = new wxLocale( userLanguage, wxLOCALE_CONV_ENCODING );
 

        // add locale search paths

        locale->AddCatalogLookupPathPrefix(PathFinder::GetInstalledPath()+wxT("/lang"));


 
        locale->AddCatalog(wxT("azpazeta"));
 
        if(! locale->IsOk() )
        {
            locale = new wxLocale( wxLANGUAGE_ENGLISH );
            userLanguage = wxLANGUAGE_ENGLISH;
		return false;
        }
    	}
    	else
    	{
        	locale = new wxLocale( wxLANGUAGE_ENGLISH );
        	userLanguage = wxLANGUAGE_ENGLISH;
		return false;
    	}
	return true;
}
/**
 * @brief Loads a options.ini file and returns a struct containing the user preferences
 * @return AZPOptions struct with user preferences
 * @since Azpazeta 2.1 Link
 * @see LoadOptions
 * */
AZPOptions LoadINIOptions()
{
	AZPOptions options;
	wxFileConfig* config=new wxFileConfig(wxT("azpazeta"));
	if(!config->Read(wxT("/General/fullScreen"),&options.general.fullScreen,false))
	{
		AzpLog("[WARNING] Options node doesn't exist",2);
		config->Write(wxT("/General/fullScreen"),false);
	}
	if(!config->Read(wxT("/General/developer"),&options.general.developer,false))
	{
		AzpLog("[WARNING] Developer node doesn't exist",2);
		config->Write(wxT("/General/developer"),false);
	}
	if(!config->Read(wxT("/General/divelMarketing"),&options.general.divelMarketing,true))
		config->Write(wxT("/General/divelMarketing"),true);
	if(!config->Read(wxT("/AZPScript/onlyFromMarket"),&options.azpscript.onlyFromMarket,true))
		config->Write(wxT("/AZPScript/onlyFromMarket"),true);
	if(!config->Read(wxT("/AZPScript/allowPayPal"),&options.azpscript.allowPayPal,true))
		config->Write(wxT("/AZPScript/allowPayPal"),true);
	if(!config->Read(wxT("/AZPScript/azpazetaMarketURL"),&options.azpscript.azpazetaMarketURL,wxT("http://azpazeta-market.googlecode.com/svn/trunk/AzpazetaMarket.html")))
		config->Write(wxT("/AZPScript/azpazetaMarketURL"),wxT("http://azpazeta-market.googlecode.com/svn/trunk/AzpazetaMarket.html"));
	if(!config->Read(wxT("/Net/divelAppsURL"),&options.net.DivelAppsURL,wxT("http://divelapps.appspot.com")))
		config->Write(wxT("/Net/divelAppsURL"),wxT("http://divelapps.appspot.com"));
	if(!config->Read(wxT("/Net/autoConnect"),&options.net.autoConnect,true))
		config->Write(wxT("/Net/autoConnect"),true);
	if(!config->Read(wxT("/Net/divelTelemetry"),&options.net.divelTelemetry,true))
		config->Write(wxT("/Net/divelTelemetry"),true);
	if(!config->Read(wxT("/Net/UserAgent"),&options.net.UserAgent,wxT("Azpazeta Market/2.1")))
		config->Write(wxT("/Net/UserAgent"),wxT("Azpazeta Market/2.1"));
	if(!config->Read(wxT("/Net/DivelNetworkName"),&options.net.DivelNetworkName,wxT("Anonymous")))
		config->Write(wxT("/Net/DivelNetworkName"),wxT("Anonymous"));
	if(!config->Read(wxT("/Net/GooglePlus"),&options.net.GooglePlus,wxT("Anonymous")))
		config->Write(wxT("/Net/GooglePlus"),wxT("Anonymous"));
	
	config->Flush();
	delete config;
	return options;
}
bool SaveINIOptions(AZPOptions options)
{
	wxFileConfig* config=new wxFileConfig(wxT("azpazeta"));
	config->Write(wxT("/General/fullScreen"),options.general.fullScreen);
	config->Write(wxT("/General/developer"),options.general.developer);
	config->Write(wxT("/General/divelMarketing"),options.general.divelMarketing);
	config->Write(wxT("/AZPScript/onlyFromMarket"),options.azpscript.onlyFromMarket);
	config->Write(wxT("/AZPScript/allowPayPal"),options.azpscript.allowPayPal);
	config->Write(wxT("/AZPScript/azpazetaMarketURL"),options.azpscript.azpazetaMarketURL);
	config->Write(wxT("/Net/divelAppsURL"),options.net.DivelAppsURL);
	config->Write(wxT("/Net/autoConnect"),options.net.autoConnect);
	config->Write(wxT("/Net/divelTelemetry"),options.net.divelTelemetry);
	config->Write(wxT("/Net/UserAgent"),options.net.UserAgent);
	config->Write(wxT("/Net/DivelNetworkName"),options.net.DivelNetworkName);
	config->Write(wxT("/Net/GooglePlus"),options.net.GooglePlus);
	config->Flush();
	delete config;
	return true;
}
