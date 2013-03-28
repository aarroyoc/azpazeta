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

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
/**
* @file pathfinder.hpp
* @brief Get paths in different OS
*/

/**
* @addtogroup PathFinder
* @{
*/
namespace PathFinder{

	wxString GetUniversalExe();

	wxString GetInstalledPath();

	wxString GetUserPath();
	void Start();
}
wxString CreateUUID();
/**
* @}
*/


/**
* @class AzpPath
* @brief The better way to get the path of the executable
*/
class AzpPath
{
	public:
		AzpPath();
		/**
		* @brief Get the path of the executable in a safe mode
		* @returns The full path to the executable without the last slash
		*/
		wxString GetPath();
	private:
		wxString path;
};
#endif
