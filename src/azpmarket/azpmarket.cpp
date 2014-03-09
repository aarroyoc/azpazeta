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
#include "azpmarket.hpp"
#include "wx/sstream.h"
#include "wx/protocol/http.h"
#include "wx/progdlg.h"
#include "../app.hpp"

extern wxString azppath;

HTMLMarket::HTMLMarket() : wxDialog(NULL,wxID_ANY,_("Azpazeta Market"))
{
	SetSize(800,600);

	wxPanel* toolbar=new wxPanel(this,wxID_ANY,wxPoint(0,0),wxSize(800,80));
	wxPanel* main=new wxPanel(this,wxID_ANY,wxPoint(0,80),wxSize(800,520));
	
	

	wxImage azpazetaimg(azppath+wxT("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	wxBitmap azpscale=wxBitmap(azpazetaimg.Scale(64,64));
	wxBitmapButton* back=new wxBitmapButton(toolbar,wxID_ANY,azpscale,wxPoint(1,1));
	back->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(HTMLMarket::AzpHome),NULL,this);
	
	html=new HTMLBrowser(main);
	AZPOptions options=LoadINIOptions();
	//StartPage(options.azpscript.azpazetaMarketURL);
	html->LoadPage(options.azpscript.azpazetaMarketURL);
	title=html->GetOpenedPageTitle();
	mainpage=options.azpscript.azpazetaMarketURL;


	



}
void HTMLMarket::StartPage(wxString url)
{
	
	wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
	
	progress.Pulse(_("Getting server data"));
	wxString server=url.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
	wxString subpage=url.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetHeader(_T("User Agent"),_T("wxHTML/2.8 (")+wxGetOsDescription()+_T(") wxWidgets/2.8 AzpazetaMarket/2.0"));
	get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 	progress.Pulse(_("Connecting to server: ")+server);
	// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
	while (!get.Connect(server))  // only the server, no pages here yet ...
	    wxSleep(5);
 
	wxApp::IsMainLoopRunning(); // should return true
 	progress.Pulse(_("Accessing files"));
	// use _T("/") for index.html, index.php, default.asp, etc.
	wxInputStream *httpStream = get.GetInputStream(subpage);
	html->SetFonts(wxT("Ubuntu"),wxT("Agency FB"));
if (get.GetError() == wxPROTO_NOERR)
{
    progress.Pulse(_("Reading page"));
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
	html->SetPage(res);
	title=html->GetOpenedPageTitle();
	mainpage=url;

}
else
{
	progress.Update(100,_("Fail to connect"));
    html->SetPage(_("<h1>Error</h1>Unable to connect to the server"));
	mainpage=url;
	title=wxT("NOTEXIST");
	
}
 
wxDELETE(httpStream);
get.Close();
}
void HTMLMarket::AzpHome(wxCommandEvent& event)
{
	if(title.Cmp(html->GetOpenedPageTitle())==0)
	{
		this->Destroy();
	}else
	{
		html->LoadPage(mainpage);
	}
}
HTMLBrowser::HTMLBrowser(wxWindow* panel) : wxHtmlWindow(panel,wxID_ANY,wxPoint(1,1),wxSize(800,520))
{



}
void HTMLBrowser::OnLinkClicked(const wxHtmlLinkInfo & link)
{
	wxString webpage=link.GetHref();
	wxString protocol=webpage.BeforeFirst(':');
	//Music HTTP
	if(protocol.Cmp(wxT("music"))==0)
	{
		wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
		wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
		wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

		wxHTTP get;
		get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
		get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 		progress.Pulse(_("Connecting to server: ")+server);
		// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
		while (!get.Connect(server))  // only the server, no pages here yet ...
		    wxSleep(5);
 
		wxApp::IsMainLoopRunning(); // should return true
 		progress.Pulse(_("Accessing music"));
		// use _T("/") for index.html, index.php, default.asp, etc.
		wxInputStream *httpStream = get.GetInputStream(subpage);

		if (get.GetError() == wxPROTO_NOERR)
		{
		progress.Pulse(_("Downloading music"));
		if(!wxDirExists(PathFinder::GetUserPath()+wxT("/.azpazeta/music")))
		{
			wxMkdir(PathFinder::GetUserPath()+wxT("/.azpazeta/music"));
		}
		wxFileOutputStream out_stream(PathFinder::GetUserPath()+wxT("/.azpazeta/music/")+CreateUUID()+wxT(".ogg"));
		httpStream->Read(out_stream);
		wxMessageBox(_("Installed correctly"),_("Azpazeta Market"),wxICON_INFORMATION | wxOK);  
		}
		else
		{
		progress.Update(100,_("Fail to connect"));
		wxMessageBox(_("An error ocurred"),_("Azpazeta Market"),wxICON_ERROR | wxOK);
		}
		wxDELETE(httpStream);
		get.Close();



		
	}else if(protocol.Cmp(wxT("map"))==0)
	{
		wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
		wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
		wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

		wxHTTP get;
		get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
		get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 		progress.Pulse(_("Connecting to server: ")+server);
		// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
		while (!get.Connect(server))  // only the server, no pages here yet ...
		    wxSleep(5);
 
		wxApp::IsMainLoopRunning(); // should return true
 		progress.Pulse(_("Accessing files"));
		// use _T("/") for index.html, index.php, default.asp, etc.
		wxInputStream *httpStream = get.GetInputStream(subpage);

		if (get.GetError() == wxPROTO_NOERR)
		{
		progress.Pulse(_("Downloading map"));
		if(!wxDirExists(PathFinder::GetUserPath()+wxT("/.azpazeta/maps")))
		{
			wxMkdir(PathFinder::GetUserPath()+wxT("/.azpazeta/maps"));
		}
		wxString zipname=PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+CreateUUID()+wxT(".zip");
		wxFileOutputStream out_stream(zipname);
		httpStream->Read(out_stream);
		progress.Pulse(_("Installing map"));
	
		std::auto_ptr<wxZipEntry> entry;
		wxFFileInputStream in(zipname);
		wxZipInputStream zip(in);
		while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
		{
			// access meta-data
			wxString name = entry->GetName();
			// read 'zip' to access the entry's data
			wxString dirname=PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+name;
			if(!wxDirExists(dirname.BeforeLast('/')))
			{
				wxMkdir(dirname.BeforeLast('/'));
			}
			if(!entry->IsDir())
			{
			wxFileOutputStream out_from_zip(PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+name);
			zip.Read(out_from_zip);
			}
		}
		wxRemoveFile(zipname);
		wxMessageBox(_("Installed correctly"),_("Azpazeta Market"),wxICON_INFORMATION | wxOK); 


	
		}
		else
		{
		progress.Update(100,_("Fail to connect"));
		wxMessageBox(_("An error ocurred"),_("Azpazeta Market"),wxICON_ERROR | wxOK); 
		}
		wxDELETE(httpStream);
		get.Close();



	}else if(protocol.Cmp(wxT("http"))==0)
	//Normal HTTP
	{
		LoadPage(webpage);
	}
}
/**
 * @deprecated
 * */
void HTMLBrowser::Deprecated()
{
	wxProgressDialog progress(_("Azpazeta Market"),_("Reading user options"));
	wxString webpage=wxT("");
	progress.Pulse(_("Getting server data"));
	wxString protocol=webpage.BeforeFirst(':');
	//Music HTTP
	if(protocol.Cmp(wxT("music"))==0)
	{
		wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
		wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

		wxHTTP get;
		get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
		get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 		progress.Pulse(_("Connecting to server: ")+server);
		// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
		while (!get.Connect(server))  // only the server, no pages here yet ...
		    wxSleep(5);
 
		wxApp::IsMainLoopRunning(); // should return true
 		progress.Pulse(_("Accessing music"));
		// use _T("/") for index.html, index.php, default.asp, etc.
		wxInputStream *httpStream = get.GetInputStream(subpage);

		if (get.GetError() == wxPROTO_NOERR)
		{
		progress.Pulse(_("Downloading music"));
		if(!wxDirExists(PathFinder::GetUserPath()+wxT("/.azpazeta/music")))
		{
			wxMkdir(PathFinder::GetUserPath()+wxT("/.azpazeta/music"));
		}
		wxFileOutputStream out_stream(PathFinder::GetUserPath()+wxT("/.azpazeta/music/")+CreateUUID()+wxT(".ogg"));
		httpStream->Read(out_stream);
		AppendToPage(_("<br><h1>Installed sucesfully</h1>"));    
		}
		else
		{
		progress.Update(100,_("Fail to connect"));
		SetPage(_("<h1>Error</h1>Unable to connect to the server"));
		}
		wxDELETE(httpStream);
		get.Close();



		
	}else if(protocol.Cmp(wxT("map"))==0)
	{
		wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
		wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

		wxHTTP get;
		get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
		get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 		progress.Pulse(_("Connecting to server: ")+server);
		// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
		while (!get.Connect(server))  // only the server, no pages here yet ...
		    wxSleep(5);
 
		wxApp::IsMainLoopRunning(); // should return true
 		progress.Pulse(_("Accessing files"));
		// use _T("/") for index.html, index.php, default.asp, etc.
		wxInputStream *httpStream = get.GetInputStream(subpage);

		if (get.GetError() == wxPROTO_NOERR)
		{
		progress.Pulse(_("Downloading map"));
		if(!wxDirExists(PathFinder::GetUserPath()+wxT("/.azpazeta/maps")))
		{
			wxMkdir(PathFinder::GetUserPath()+wxT("/.azpazeta/maps"));
		}
		wxString zipname=PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+CreateUUID()+wxT(".zip");
		wxFileOutputStream out_stream(zipname);
		httpStream->Read(out_stream);
		progress.Pulse(_("Installing map"));
	
		std::auto_ptr<wxZipEntry> entry;
		wxFFileInputStream in(zipname);
		wxZipInputStream zip(in);
		while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
		{
			// access meta-data
			wxString name = entry->GetName();
			// read 'zip' to access the entry's data
			wxString dirname=PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+name;
			if(!wxDirExists(dirname.BeforeLast('/')))
			{
				wxMkdir(dirname.BeforeLast('/'));
			}
			if(!entry->IsDir())
			{
			wxFileOutputStream out_from_zip(PathFinder::GetUserPath()+wxT("/.azpazeta/maps/")+name);
			zip.Read(out_from_zip);
			}
		}
		wxRemoveFile(zipname);
		AppendToPage(_("<br><h1>Installed sucesfully</h1>"));


	
		}
		else
		{
		progress.Update(100,_("Fail to connect"));
		SetPage(_("<h1>Error</h1>Unable to connect to the server"));
		}
		wxDELETE(httpStream);
		get.Close();



	}else if(protocol.Cmp(wxT("http"))==0)
	//Normal HTTP
	{
		wxString server=webpage.AfterFirst('/').AfterFirst('/').BeforeFirst('/');
		wxString subpage=webpage.AfterFirst('/').AfterFirst('/').AfterFirst('/').Prepend(_("/"));

		wxHTTP get;
		get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
		get.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

 		progress.Pulse(_("Connecting to server: ")+server);
		// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
		while (!get.Connect(server))  // only the server, no pages here yet ...
		    wxSleep(5);
 
		wxApp::IsMainLoopRunning(); // should return true
 		progress.Pulse(_("Accessing files"));
		// use _T("/") for index.html, index.php, default.asp, etc.
		wxInputStream *httpStream = get.GetInputStream(subpage);

		if (get.GetError() == wxPROTO_NOERR)
		{
		progress.Pulse(_("Reading page"));
		wxString res;
		wxStringOutputStream out_stream(&res);
		httpStream->Read(out_stream);
		SetPage(res);
		}
		else
		{
		progress.Update(100,_("Fail to connect"));
		SetPage(_("<h1>Error</h1>Unable to connect to the server"));
		}
		wxDELETE(httpStream);
		get.Close();

	}
	
}
