
#include "azpmap.hpp"
#include "stdlib.h"
#include "../xml/tinyxml.h"
/* Read TMX files from Tiled Map Editor, get meta information ,create ArrayData for OpenGL and create EventData for AzpVM*/

/*IMPORTANT: ORDER OF TMX TILESETS

BLUEANDRED
HOUSE1

Important for use it later in GL Display
*/


AzpMap::AzpMap(wxString file)
{
	TiXmlDocument doc(file.mb_str());
	if(!doc.LoadFile())
	{
		wxLogError(_("Failed to load the selected map: ")+file);
	}
	TiXmlElement* properties, *property,*tileset,*layer,*data,*tile;
	TiXmlElement* azpazeta_map=doc.RootElement();
	while(azpazeta_map)
	{
		properties=azpazeta_map->FirstChildElement("properties");
		while(properties)
		{
			property=properties->FirstChildElement("property");
			while(property)
			{
			if(strcmp(property->Attribute("name"),"Name")==0)
			{
				property->Attribute("value");
			}
			if(strcmp(property->Attribute("name"),"Author")==0)
			{
				property->Attribute("value");
			}
			if(strcmp(property->Attribute("name"),"MinVersion")==0)
			{
				const char* minversion=property->Attribute("value");
				if(strcmp(minversion,"JUNO")!=0)
					if(strcmp(minversion,"ORIGINAL")!=0)
						if(strcmp(minversion,"ALL")!=0)
							wxLogError(_("This map requires an updated version of Azpazeta"));
			}
			if(strcmp(property->Attribute("name"),"Year")==0)
			{
				property->Attribute("value");
			}

			property=property->NextSiblingElement("property");
		}
		properties=properties->NextSiblingElement("properties");


		tileset=azpazeta_map->FirstChildElement("tileset");
		int counttileset=0;
		while(tileset)
		{
		
		
		if(strcmp(tileset->Attribute("name"),"BlueAndRed")==0)
		{
			TileSets[counttileset][0]=BLUE_AND_RED_TILES;
			TileSets[counttileset][1]=atoi(tileset->Attribute("firstgid"));
		}
		if(strcmp(tileset->Attribute("name"),"VADRIX")==0)
		{
			TileSets[counttileset][0]=VADRIX_TILES;
			TileSets[counttileset][1]=atoi(tileset->Attribute("firstgid"));
		}
		counttileset++;
		tileset=tileset->NextSiblingElement("tileset");
		}

		layer=azpazeta_map->FirstChildElement("layer");
		while(layer)
		{
		data=layer->FirstChildElement("data");
		while(data)
		{
		tile=data->FirstChildElement("tile");
		int x=0,y=0;
		while(tile)
		{
			ArrayData[x][y]=atoi(tile->Attribute("gid"));
			//wxMessageBox(wxString::Format(wxT("Part 1: %d"),ArrayData[x][y]));
			//printf("DATA-FROM-MAP: %d\n",atoi(tile->Attribute("gid")));
			if(x==19) //x==19
			{
				x=0;y++;
			}else{
			x++;
			}
	

			tile=tile->NextSiblingElement("tile");
		}
		//printf("READING MAP... [100]\nX->%d\nY->%d\n",x,y);
		



		data=data->NextSiblingElement("data");
		}

		layer=layer->NextSiblingElement("layer");
		}



		}
		azpazeta_map=azpazeta_map->NextSiblingElement("map");
	}



}
AzpMapData AzpMap::GetData()
{
	return map;

}
int64_t AzpMap::GetArrayData(int posx,int posy)
{
	//wxMessageBox(wxString::Format(wxT("Part 2: %d"),ArrayData[posx][posy]));
return ArrayData[posx][posy];
}
