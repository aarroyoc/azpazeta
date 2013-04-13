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
#include "map.hpp"
#include "../xml/tinyxml.h"
/* Read mount.xml or info.xml file to get the main map and meta information */

AzpMount::AzpMount(wxString mount_xml_file)
{
	TiXmlDocument doc(mount_xml_file.mb_str());
	if(!doc.LoadFile())
	{
		wxLogError(_("Failed to load the selected map: ")+mount_xml_file);
	}
	TiXmlElement *meta_data, *map_main;
	TiXmlElement *azpazeta_map=doc.RootElement();
	while(azpazeta_map)
	{
		//Parsear cada uno
		//Meta Data TODO
		meta_data=azpazeta_map->FirstChildElement("meta-data");
		while(meta_data)
		{

		meta_data=meta_data->NextSiblingElement("meta-data");
		}
		//Main Map DONE
		map_main=azpazeta_map->FirstChildElement("map-main");
		while(map_main)
		{
			mainmap=wxString::FromUTF8(map_main->GetText());
		map_main=map_main->NextSiblingElement("map-main");
		}

		azpazeta_map=azpazeta_map->NextSiblingElement("azpazeta-map");
	}



}
