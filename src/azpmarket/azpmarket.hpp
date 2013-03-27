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
#ifndef AZPMARKET_HPP
#define AZPMARKET_HPP
#include "wx/wx.h"
#include "wx/wxhtml.h"
class HTMLBrowser : public wxHtmlWindow
{
	public:
		HTMLBrowser(wxWindow* panel);
	private:
		virtual void OnLinkClicked(const wxHtmlLinkInfo & link);
};
class HTMLMarket : public wxDialog
{
	public:
		HTMLMarket();
			
	private:
		wxString mainpage;
		wxString title;
		HTMLBrowser* html;
		void AzpHome(wxCommandEvent&);
		void StartPage(wxString);
};


#endif
