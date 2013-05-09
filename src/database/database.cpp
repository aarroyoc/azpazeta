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

#include "database.hpp"
#include "../xml/tinyxml.h"

DATABASE::DATABASE(wxString file)
{
	databasefile=file;
	TiXmlDocument doc(file.mb_str());
	if(!doc.LoadFile())
	{
		wxLogError(_("Failed to load the selected database")+file);
	}
	TiXmlElement* var;
	TiXmlElement* database=doc.RootElement();
	while(database)
	{
		var=database->FirstChildElement("var");
		read=0;
		while(var)
		{
			VarArray[read]=wxString::FromUTF8(var->Attribute("name"));
			read++;
			VarArray[read]=wxString::FromUTF8(var->Attribute("value"));
			read++;

			var=var->NextSiblingElement("var");
		}
		database=database->NextSiblingElement("database");
	}

}

wxString DATABASE::Get(wxString attribute)
{
	int readnow;
	for(readnow=0;readnow<read;readnow+=2)
	{
		if(VarArray[readnow].Cmp(attribute)==0)
		{
			return VarArray[readnow+1];

		}

	}
	return wxT("NOTEXIST");
	

}
void DATABASE::Set(wxString attribute,wxString value)
{
	TiXmlDocument doc(databasefile.mb_str());
	if(!doc.LoadFile())
	{
		wxLogError(_("Failed to load the selected database")+databasefile);
	}
	TiXmlElement* var;
	TiXmlElement* database=doc.RootElement();
	while(database)
	{
		var=database->FirstChildElement("var");
		read=0;
		while(var)
		{
			if(strcmp(attribute.mb_str(),var->Attribute("name"))==0)
			{
				var->SetAttribute("value",value.mb_str());
			}

			var=var->NextSiblingElement("var");
		}
		database=database->NextSiblingElement("database");
	}
	doc.SaveFile();


}
