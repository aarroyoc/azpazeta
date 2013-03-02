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
 * @file pathfinder.cpp
 * @brief Get some paths in the current Operating System
 * @author Adrián Arroyo Calle
 */
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "wx/wx.h"


/**
 * @brief Get the Dir of the executable
 * @returns The directory of the executable
 */
wxString GetUniversalDir(){
	#ifdef WIN32
	#define MAX_PATH 2048
	WCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, ARRAYSIZE(path));
	strcat(path,"_FOLDER");
	
	return wxString::FromUTF8(path);
	#else
	#define BUFSIZ 2048
	char buffer[BUFSIZ];
  	readlink("/proc/self/exe", buffer, BUFSIZ); //Se obtiene ejecutable, no directorio
	strcat(buffer,"_FOLDER");
	return wxString::FromUTF8(buffer);
	#endif



}
