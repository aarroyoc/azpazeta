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
#include "pathfinder.hpp"
#include "wx/datetime.h"

#ifdef UUID
extern "C"
{
#ifdef WIN32
#include <Rpc.h>
#else
#include <uuid/uuid.h>
#endif
}
#endif

wxString azppath;


void PathFinder::Start()
{

	azppath=PathFinder::GetInstalledPath();
	
}
/**
 * @brief Get the Dir of the executable
 * @returns The directory of the executable
 */
wxString PathFinder::GetUniversalExe(){
	#ifdef WIN32
	#define MAX_PATH 2048
	WCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, ARRAYSIZE(path));
	
	return wxString(path);
	#elif BSD
	char buffer[BUFSIZ];
	readlink("/proc/curproc/exe",buffer,BUFSIZ);
	return wxString::FromUTF8(buffer);
	#elif BASH
	char buffer[BUFSIZ];
	buffer=getenv("_");
	return wxString::FromUTF8(buffer);
	#else //Linux
	char buffer[BUFSIZ];
  	ssize_t tamano=readlink("/proc/self/exe", buffer, BUFSIZ); //Se obtiene ejecutable, no directorio
	return wxString::FromUTF8(buffer);
	#endif



}
wxString CreateUUID()
{
#ifdef UUID
/* UUID Native Implementation */
#ifdef WIN32
    UUID uuid;
    UuidCreate ( &uuid );

    unsigned char * str;
    UuidToStringA ( &uuid, &str );

    std::string s( ( char* ) str );

    RpcStringFreeA ( &str );
#else
    uuid_t uuid;
    uuid_generate_random ( uuid );
    char s[37];
    uuid_unparse ( uuid, s );
#endif
    return wxString::FromUTF8(s);
#elif DATETIME
/* Date-Time Implementation*/
wxDateTime now=wxDateTime::UNow();
return wxString(now.Format());
#else
srand(time(NULL));
int randnumber=rand()%1000; //Range between 0-1000
return wxString::Format(wxT("%d"),randnumber);


#endif
}
/**
* @brief Get the Path of the installation
* @returns The path of the installations
* @verbatim
Example:
Azpazeta binary installed in /opt/azpazeta/AZPAZETA_JUNO returns /opt/azpazeta. Azpazeta binary installed in C:\Program Files (x86)\Azpazeta\Azpazeta.exe returns C:\Program Files (x86)\Azpazeta
* @endverbatim
*/
wxString PathFinder::GetInstalledPath()
{
	wxString exe=PathFinder::GetUniversalExe();
	wxString path;
	#ifdef WIN32
	path=exe.BeforeLast('\\');
	#else
	path=exe.BeforeLast('/');
	#endif
	return path;

}
/**
* @brief Get the Path of the current user
* @returns The path of the current user
* @verbatim
Example:
Current user is James the function returns /home/james/.azpazeta or C:\Users\james\AppData\Roaming\.azpazeta
* @endverbatim
*/
wxString PathFinder::GetUserPath()
{
	#ifdef WIN32
	const char* home="APPDATA";

	#else
	const char* home="HOME";

	#endif
	char* homePath=getenv(home);
	char localPath[1024];
	strcpy(localPath,homePath);
	return wxString::FromUTF8(localPath);
}

AzpPath::AzpPath()
{
	wxString exe=PathFinder::GetUniversalExe();
	#ifdef WIN32
	path=exe.BeforeLast('\\');
	#else
	path=exe.BeforeLast('/');
	#endif
}
wxString AzpPath::GetPath()
{
	return path;
}
