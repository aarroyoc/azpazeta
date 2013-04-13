
#include "azpmap.hpp"
#include "stdlib.h"
#include "../xml/tinyxml.h"
/* Read TMX files from Tiled Map Editor, get meta information ,create ArrayData for OpenGL and create EventData for AzpVM*/


AzpMap::AzpMap(wxString file)
{
	TiXmlDocument doc(file.mb_str());
	if(!doc.LoadFile())
	{
		wxLogError(_("Failed to load the selected map")+file);
	}
	TiXmlElement* background, *inside,*sides,*tile;
	TiXmlElement* azpazeta_map=doc.RootElement();
	while(azpazeta_map)
	{
		//Parsear cada uno
		//Background DONE
		background=azpazeta_map->FirstChildElement("background");
		while(background)
		{
			if(strcmp(background->GetText(),"AZPAZETA_THEME")==0)
			{
				//Apply Azpazeta Theme
				map.background.theme=AZPAZETA_THEME;
			}
			background=background->NextSiblingElement("background");
		}
		
		//Main Data DONE
		inside=azpazeta_map->FirstChildElement("inside");
		while(inside)
		{
			tile=inside->FirstChildElement("tile");
			while(tile)
			{
			
			map.inside.tile[atoi(tile->Attribute("posX"))][atoi(tile->Attribute("posY"))]=wxString::FromUTF8(tile->GetText());
			//Events DONE
			map.inside.onenter[atoi(tile->Attribute("posX"))][atoi(tile->Attribute("posY"))]=wxString::FromUTF8(tile->Attribute("onenter"));
			map.inside.onstay[atoi(tile->Attribute("posX"))][atoi(tile->Attribute("posY"))]=wxString::FromUTF8(tile->Attribute("onstay"));
			tile=tile->NextSiblingElement("tile");
			}
			inside=inside->NextSiblingElement("inside");
		}

		azpazeta_map=azpazeta_map->NextSiblingElement("map");
		//Other maps TODO- SIDES TODO TODO TODO
		
	}



}
AzpMapData AzpMap::GetData()
{
	return map;

}
