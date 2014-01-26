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



#include <fstream>
#include <iostream>
#include "wx/zipstrm.h"
#include "../xml/tinyxml.h"
#include "savefile.hpp"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"
#include "../version.hpp"
#include "wx/progdlg.h"
#include <memory>
#include <config.h>
extern double azpmoney;
extern wxString azpname;
extern int vadrixchar;

SaveFile::SaveFile(wxString file)
{
fileuri=file;
	


}
bool SaveFile::LoadAll()
{
char superbuffer[8192];
wxProgressDialog pd(_("Loading savefile"),_("Loading data"),5);
pd.Update(1);
std::auto_ptr<wxZipEntry> entry;
wxFFileInputStream in(fileuri);
wxZipInputStream zip(in);
do{

    entry.reset(zip.GetNextEntry());

}while(entry.get() != NULL && entry->GetInternalName() != _("AZP-DATA/main.xml"));
pd.Update(2);
if(entry.get() != NULL)
{
	zip.Read(superbuffer,8192);
}else
{
pd.Pulse(_("Wrong Azpazeta package format"));
wxSleep(5000);
pd.Update(6);
return false;
}
pd.Update(3);
//READING SUPERBUFFER
TiXmlDocument doc;
doc.Parse(superbuffer,0,TIXML_ENCODING_UTF8);
TiXmlElement *var;
TiXmlElement* savefile=doc.RootElement();
pd.Update(4);
while(savefile)
{
	var=savefile->FirstChildElement("var");
	while(var)
	{
		if(strcmp(var->Attribute("name"),"azpmoney")==0)
		{
			azpmoney=atof(var->GetText());
		}
		if(strcmp(var->Attribute("name"),"vadrixchar")==0)
		{
			vadrixchar=atoi(var->GetText());
		}
		if(strcmp(var->Attribute("name"),"azpname")==0)
		{
			azpname=wxString::FromUTF8(var->GetText());
		}
		var=var->NextSiblingElement("var");
	}
	savefile=savefile->NextSiblingElement("savefile");
}
pd.Update(5);
pd.Update(6);



}
bool SaveFile::SaveAll()
{
	wxFFileOutputStream out(fileuri);
	wxZipOutputStream zip(out);
	wxTextOutputStream txt(zip);
	wxString sep(wxFileName::GetPathSeparator());
	//DEPRECATED
	char datosparaguardar[2048];
	zip.PutNextEntry(wxT("AZPGeneral.txt"));
	sprintf(datosparaguardar,"Azpazeta_Save_File_v.2.0"); //Deprecated, from 1.0
	txt << wxString::FromUTF8(datosparaguardar);
	zip.PutNextEntry(wxT("SERVER-DATA")+ sep+ wxT("lastservers.txt")); //Deprecated, from 1.0
	zip.PutNextEntry(wxT("META-DATA") + sep + wxT("INFO.txt")); //Deprecated, from 1.0
	txt << wxT("Hi, this is the user information\n");

	//NOT USED IN AZPAZETA, BUT UTIL
	zip.PutNextEntry(wxT("META-DATA")+ sep + wxT("VERSION.HTML"));
	txt << wxT("MinVersion: JUNO\n");
	txt << wxString::Format(wxT("<h1>Azpazeta Version Information</h1><h2>Version</h2><p>Major version: %d<br>Minor version: %d<br>Patch version: %d<br>Version name: %s<br>AZPScript Version: %d</p>"),AZPAZETA_VERSION_MAJOR,AZPAZETA_VERSION_MINOR,AZPAZETA_VERSION_PATCH,AZPAZETA_WX_NAME,AZPSCRIPT_VERSION);

	//Compiling options
        txt << wxT("<h2>Compile configuration</h2><p>Compiler: ");
	txt << wxString::FromUTF8("Unknow"); //AZP_COMPILER
	txt << wxT("<br>CMake Version: ");
	txt << wxString::FromUTF8("Unkown"); //AZP_CMAKE_VERSION
	txt << wxT("<br>Operating System: ");
	txt << wxString::FromUTF8("Unknow"); //AZP_SYSTEM
	txt << wxT("<br>Processor: ");
	txt << wxString::FromUTF8("Unknow"); //AZP_PROCESSOR
	txt << wxT("<br>wxWidgets Version String: ");
	txt << wxVERSION_STRING;
	txt << wxT("<br></p>");//COMPILER_WX,CMAKE_WX_VERSION,OS_WX,PROCESSOR_WX,wxMAJOR_VERSION,wxMINOR_VERSION);
	txt << wxT("<h2>Runtime values</h2><p>Host name: ");
	txt << wxGetHostName();
	txt << wxT("<br>Operating System: ");
	txt << wxGetOsDescription();
	txt << wxT("<br>Little endian: ");
	txt << (wxIsPlatformLittleEndian() ? wxT("Yes") : wxT("No"));
	txt << wxT("<br>Native 64 bits: ");
	txt << (wxIsPlatform64Bit() ? wxT("Yes") : wxT("No"));
	zip.PutNextEntry(wxT("META-DATA")+ sep + wxT("LASTUPDATE.TXT"));
	txt << wxNow() << wxT(" WITH JUNO");

	//ALWAYS
	//First create XML with TinyXML, later pass it to the ZIP
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	TiXmlElement * savefile = new TiXmlElement( "savefile" );
	TiXmlElement* varmoney=new TiXmlElement("var");
	varmoney->SetAttribute("name","azpmoney");
	char buffer[8192];
	sprintf(buffer,"%f",azpmoney);
	varmoney->LinkEndChild(new TiXmlText(buffer));
	savefile->LinkEndChild(varmoney);
	TiXmlElement* varname=new TiXmlElement("var");
	varname->SetAttribute("name","azpname");
	sprintf(buffer,"%s",(const char*)azpname.mb_str());
	varname->LinkEndChild(new TiXmlText(buffer));
	savefile->LinkEndChild(varname);
	TiXmlElement* varvadrixchar=new TiXmlElement("var");
	varvadrixchar->SetAttribute("name","vadrixchar");
	sprintf(buffer,"%d",vadrixchar);
	varvadrixchar->LinkEndChild(new TiXmlText(buffer));
	savefile->LinkEndChild(varvadrixchar);
	/*TiXmlText * text = new TiXmlText( "World" );
	element->LinkEndChild( text );*/
	doc.LinkEndChild( decl );
	doc.LinkEndChild( savefile );
	zip.PutNextEntry(wxT("AZP-DATA/main.xml"));
	TiXmlPrinter printer;
	printer.SetStreamPrinting ();
	doc.Accept (&printer);

	txt << wxString::FromUTF8(printer.CStr ());
}
