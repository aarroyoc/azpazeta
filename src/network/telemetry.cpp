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

#include "telemetry.hpp"

Telemetry::Telemetry(wxString trackingid,wxString appname,wxString version,wxString window, wxString screen, wxString language)
{
trackingid_pr=trackingid;
appname_pr=appname;
version_pr=version;
window_pr=window;
screen_pr=screen;
language_pr=language;




}

void Telemetry::Send()
{
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	//get.SetHeader(_T("User Agent"),_T("wxHTML/2.8 (")+wxGetOsDescription()+_T(") wxWidgets/2.8 AzpazetaMarket/2.0")); Older UserAgent
	get.SetHeader(_T("User Agent"),_T("Azpazeta/2.0 (")+wxGetOsDescription()+_T(") wxHTML/2.8"));
	//printf((_T("Azpazeta/2.0 (")+wxGetOsDescription()+_T(") wxHTML/2.8")).mb_str());
	get.SetTimeout(10);
	while (!get.Connect(wxT("www.google-analytics.com")))  // only the server, no pages here yet ...
	    wxSleep(5);
	wxString GETrequest=wxT("/collect?payload_data&v=1&tid=");
	GETrequest.Append(trackingid_pr);
	GETrequest.Append(wxT("&cid=555&t=appview&an="));
	GETrequest.Append(appname_pr);
	GETrequest.Append(wxT("&av="));
	GETrequest.Append(version_pr);
	GETrequest.Append(wxT("&cd="));
	GETrequest.Append(window_pr);
	GETrequest.Append(wxT("&sr="));
	GETrequest.Append(screen_pr);
	GETrequest.Append(wxT("&ul="));
	GETrequest.Append(language_pr);//"),window_pr,screen_pr,language_pr;
	wxInputStream *httpStream = get.GetInputStream(GETrequest);
	if (get.GetError() == wxPROTO_NOERR)
	{
	    wxString res;
	    wxStringOutputStream out_stream(&res);
	    httpStream->Read(out_stream);
		

	}
	else
	{
		wxMessageBox(_("Failed to submit data to Divel Telemetry"),_("Divel Telemetry"),wxICON_WARNING|wxOK);
	
	}
	 
	wxDELETE(httpStream);
	get.Close();
}
