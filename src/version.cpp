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

//Add Version frame TODO
#include "wx/aboutdlg.h"
#include "version.hpp"
#include "wx/wxhtml.h"
void Version::Display::About()
{
	wxAboutDialogInfo info;
	info.AddArtist(wxT("Adrián Arroyo Calle"));
	info.AddArtist(wxT("Raúl Izquierdo Buznego"));
	info.AddArtist(wxT("Pablo Izquierdo Buznego"));
	info.AddDeveloper(wxT("Adrián Arroyo Calle"));
	info.AddDocWriter(wxT("Adrián Arroyo Calle"));
	info.AddDocWriter(wxT("Raúl Izquierdo Buznego"));
	info.AddTranslator(wxT("Adrián Arroyo Calle->Spanish"));
	info.AddTranslator(wxT("Google Translate->French"));
	info.SetDescription(_("Azpazeta is a strategy-economic game about Vadrix and the region of Azpazeta. Explore the world in a sandbox game"));
	info.SetLicense(wxT("GPLv2"));
	info.SetName(wxT("Azpazeta"));
	info.SetVersion(wxString::FromUTF8(AZPAZETA_VERSION_STR));
	info.SetWebSite(wxT("http://launchpad.net/azpazeta"));
	wxAboutBox(info);
}
void Version::Display::All()
{
	//wxHTML, create class VersionHTML and put all the data in this file TODO
}
