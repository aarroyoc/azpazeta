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

#include "event.hpp"
#include "../xml/tinyxml.h"
#include "azpvm.hpp"


EventManager::EventManager(wxString tmxmap)
{
	wxString eventmap=(tmxmap.BeforeLast('.'))+wxT("-event.xml");
	#ifdef WIN32
	scriptpath=eventmap.BeforeLast('\\');

	#else
	scriptpath=eventmap.BeforeLast('/');


	#endif
	if(!wxFileExists(eventmap))
	{
		wxLogError(_("The selected EventTable doesn't exist"));
	}
	TiXmlDocument doc(eventmap.mb_str());
	if(!doc.LoadFile())
	{
		//wxLogError(_("Failed to load the selected event table for map: ")+tmxmap+_("\nThe EventTable: ")+eventmap);
	}
	TiXmlElement *info,*side,*data,*tile;
	TiXmlElement* event_table=doc.RootElement();
	while(event_table)
	{
		data=event_table->FirstChildElement("data");
		while(data)
		{
			tile=data->FirstChildElement("tile");
			int x=0,y=0;
			while(tile)
			{
				const char* archive=tile->Attribute("onstay");
				wxString file;
				if(archive==NULL)
					file=wxT("NULL");
				else
					file=wxString::FromUTF8(archive);
				EventArray[x][y]=file;

				if(x==19) //x==19
				{
					x=0;y++;
				}else{
				x++;
				}





				tile=tile->NextSiblingElement("tile");
			}
			//printf("READING EVENTS... [100]\nX->%d\nY->%d\n",x,y);		
		

			data=data->NextSiblingElement("data");
		}


		info=event_table->FirstChildElement("info");
		while(info)
		{
			side=info->FirstChildElement("side");
			while(side)
			{
				if(strcmp(side->Attribute("side"),"up")==0)
				{
					MapArray[MAP_UP]=wxString::FromUTF8(side->GetText());
				}
				if(strcmp(side->Attribute("side"),"down")==0)
				{
					MapArray[MAP_DOWN]=wxString::FromUTF8(side->GetText());
				}
				if(strcmp(side->Attribute("side"),"left")==0)
				{
					MapArray[MAP_LEFT]=wxString::FromUTF8(side->GetText());
				}
				if(strcmp(side->Attribute("side"),"right")==0)
				{
					MapArray[MAP_RIGHT]=wxString::FromUTF8(side->GetText());
				}


			
				side=side->NextSiblingElement("side");
			}
			info=info->NextSiblingElement("info");
		}

		event_table=event_table->NextSiblingElement("event-table");
	}
}

wxString EventManager::Execute(int x, int y)
{
	if(EventArray[x][y].Cmp(wxT("NULL"))==0)
		return wxT("NOTEXIST");
	else
	{
		AZPVM* azpvm=new AZPVM(scriptpath+wxT("/")+EventArray[x][y],azpVM_SECURE);
		return wxT("[OK] Running map script");

	}
}
wxString EventManager::ChangeMap(int side)
{
	if(MapArray[side].Cmp(wxT("NULL"))==0)
		return wxT("NULL");
	else
		return scriptpath+wxT("/")+MapArray[side];


}
