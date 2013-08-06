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
#ifdef WIN32
#include <windows.h>
#endif

#include "log.hpp"

static const char blue[]="\e[1;34m"; //Status and Info messages
static const char black[]="\e[0m"; //Long messages
static const char red[]="\e[0;31m"; //Error messages
static const char green[]="\e[0;32m"; //Sucessfully messages
static const char yellow[]="\e[0;33m"; //Warning messages

void AzpLog(const char* message, int level)
{
	switch(level)
	{
		case 1:blueprintf(message);break;
		case 2:yellowprintf(message);break;
		case 3:redprintf(message);break;
		case 4:greenprintf(message);break;
		default:break;
	
	}
}
void blueprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",blue,message,black);

#endif
}
void redprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",red,message,black);

#endif
}
void yellowprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",yellow,message,black);

#endif
}
void greenprintf(const char* message)
{
#ifdef WIN32
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	printf("%s",message);
	SetConsoleTextAttribute(hConsole,15);
	printf("\n");
#else
	printf("%s%s%s\n",green,message,black);

#endif
}
