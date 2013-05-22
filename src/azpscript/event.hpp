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
#include "../maploader/azpmap.hpp"


#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#define MAP_UP 0
#define MAP_DOWN 1
#define MAP_LEFT 2
#define MAP_RIGHT 3

class EventManager{
	public:
		EventManager(wxString tmxmap);
		wxString Execute(int x, int y);
		wxString ChangeMap(int side);
	private:
		wxString EventArray[20][20];
		wxString MapArray[MAP_RIGHT+1];
		wxString scriptpath;
		
};
#endif
