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
#ifndef VERSION_HPP
#define VERSION_HPP

#define AZPAZETA_VERSION_MAJOR 2
#define AZPAZETA_VERSION_MINOR 0
#define AZPAZETA_VERSION_PATCH 0
#define AZPAZETA_VERSION_STR "2.0.0"
#define AZPAZETA_NAME "JUNO"
#define AZPAZETA_WX_NAME wxT("JUNO")
#define AZPSCRIPT_VERSION 1

#ifndef COMPILER_WX
#define COMPILER_WX wxT("Unknow")
#endif
#ifndef CMAKE_WX_VERSION
#define CMAKE_WX_VERSION wxT("Unknow")
#endif
#ifndef OS_WX
#define OS_WX wxT("Unknow")
#endif
#ifndef PROCESSOR_WX
#define PROCESSOR_WX wxT("Unknow")
#endif



#include "wx/wx.h"
#include "wx/wxhtml.h"
namespace Version{
	namespace Display{
		void About();
		void All();
	}


}

class HTMLVersion : public wxDialog
{
	public:
		HTMLVersion();
	private:
		wxHtmlWindow* html;
};


#endif
