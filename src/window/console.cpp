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
 * @file console.cpp
 * @brief Window for Logging events in Azpazeta and AzpVM
 * @author Adrián Arroyo Calle
 * @date 02/03/2013
 */

#include "console.hpp"
#include "wx/utils.h"
#include "../pathfinder/pathfinder.hpp"

AZPLogWindow::AZPLogWindow()
{
	wxLogWindow* log=new wxLogWindow(NULL,wxT("AZPLog Window"),true);
	wxLog::SetVerbose(true);
	wxLogVerbose(wxT("[AZPLOG] Init AZPLogWindow"));
	/*wxLogInfo(wxT("[AZPLOG] Init AZPLogWindow"));
	wxLogGeneric(wxLOG_Info,wxT("[AZPLOG] Init AZPLogWindow"));
	wxLogMessage(wxT("[AZPLOG] Init AZPLogWindow"));*/
	wxString runningon=wxT("[AZPLOG] Running on ");
	runningon.Append(wxGetOsDescription());
	wxLogStatus(runningon);
	wxLogVerbose(wxT("[AZPLOG] Running Azpazeta in ")+PathFinder::GetInstalledPath());
	wxLogWarning(wxT("[AZPLOG] Running Azpazeta as developer"));
}
