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
/**
@file options.hpp
@brief Options dialog
*/
#ifndef OPTIONS_HPP
#define OPTIONS_HPP
#include "../app.hpp"
#include "wx/glcanvas.h"
#include "testgl.hpp"
/**
 * @enum OptionsEnum
 * @brief Events ID for buttons
 */
enum{
	CHECK_NEW_VERSION,
	APPLY_OPTIONS,
	OK_OPTIONS,
	CANCEL_OPTIONS,
	SEE_VERSION,
	GO_WEB,
	GO_MARKET,
	MANAGE_MAPS

};
/** 
 * @class Options
 * @brief Options dialog
 */
typedef class Options : public wxDialog
{
public:
	Options(const wxString& title); //Constructor
	BasicGLPane* glPane;
	void OnClose(wxCloseEvent& event);
private:
	void Apply(wxCommandEvent& event);
	void Cancel(wxCommandEvent& event);
	void Ok(wxCommandEvent& event);
	void Tab(wxCommandEvent& event);
	void SeeVersion(wxCommandEvent& event);
	void LaunchWebSite(wxCommandEvent& event);	
	void SaveXMLData();
	void SaveINIData();
	//General
	wxChoice* getLanguage;
	wxCheckBox* fullScreen;
	wxCheckBox* developer;
	wxCheckBox* divelMarketing;
	wxButton* seeVersion;
	wxButton* goWebpage;
	//AZPScript
	wxCheckBox* onlyFromMarket;
	wxTextCtrl* XazpazetaMarketURL; 
	wxCheckBox* allowPayPal;
	wxButton* goMarket;
	wxButton* manageAddons;
	
	//Net
	wxTextCtrl* XdivelAppsUrl;
	wxCheckBox* autoConnect;
	wxButton* checkNewVersion;
	wxTextCtrl* XdivelNetwork;
	wxTextCtrl* Xgoogleplus;
	wxCheckBox* divelTelemetry;
	//All
	wxButton* optOk;
	wxButton* optCancel;
	

} Options;




#endif
