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

#include "wx/wx.h"

typedef enum{
SAVEFILE_NAME,
SAVEFILE_AGE,
SAVEFILE_MONEY,
SAVEFILE_DATE,
SAVEFILE_PLAYER,
SAVEFILE_SKIN,
SAVEFILE_AUTOSAVE,
SAVEFILE_MISSIONS,
SAVEFILE_VERSION

}SAVEFILE_PARAMETERS;


class SaveFile{
public:
	SaveFile(wxString file);
	bool LoadAll();
	bool SaveAll();
	wxString Read(SAVEFILE_PARAMETERS parameter);
	bool Set(SAVEFILE_PARAMETERS parameter, wxString value);
};
