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
#ifndef MAP_HPP
#define MAP_HPP
/**
* @class AzpMap
* @brief Load a Map
*/

#include "wx/wx.h"
//wxString AzpData[1024];

typedef enum{
	AZPAZETA_THEME,
	DESERT_THEME
} AZPTHEME;

typedef struct{
	wxString title;
	wxString author;
	wxString description;
	wxString homesite;
} AzpMetaData;

typedef struct{
	struct background{
	
		AZPTHEME theme;
	}background;

	struct inside{
		wxString tile[100][100];
		wxString onenter[100][100];
		wxString onstay[100][100];
	}inside;
	struct sides{
		wxString right;
		wxString left;
		wxString up;
		wxString down;
	}sides;


} AzpMapData;

class AzpMount{
	public:
		AzpMount(wxString mount_xml_file);
		bool LoadAzpMap(wxString file);
		bool LoadNextMap(int side);
		bool GetImage(int x, int y);
		wxString GetMetadata();
		wxString mainmap;
		AzpMetaData GetMetaData();
	private:
		AzpMetaData metadata;

};
#endif
