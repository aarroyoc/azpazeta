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

#include "xml/tinyxml.h"

IMPLEMENT_APP(Azpazeta)

AzpClient* client;
extern wxString azppath;

bool Azpazeta::OnInit()
{
	AzpLog("[INFO] Welcome to Azpazeta!",1);
	AzpLog("[INFO] Running JUNO",1);
    // create the main application window
    //Init wxLocale funcionality
    if(!InitWxLocale())
	{
		wxMessageBox(_("Your language doesn't appear in Azpazeta translations. Please, create a translation in translations.launchpad.net/azpazeta"));
		AzpLog("[WARNING] This language doesn't appear in Azpazeta Translations",2);
	}
	AzpLog("[OK] Localization",4);

	PathFinder::Start();
	AzpLog("[OK] PathFinder gets Azpazeta Resources Dir",4);
	Notify();

	//TaskBar Icon
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


	Start *frame = new Start(_("Azpazeta Juno"));

	    // and show it (the frames, unlike simple controls, are not shown when
	    // created initially)
	frame->Show(true);

		//Start Dialog
	StartDialog* stdg=new StartDialog();
	stdg->ShowModal();

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
	wxShell(wxT("notify-send -i azpazeta \"Azpazeta\" \"Welcome to Azpazeta 2.0 Juno\""));

	#endif 


}
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
