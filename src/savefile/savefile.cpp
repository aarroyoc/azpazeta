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

extern double azpmoney;
#include <fstream>
#include <iostream>
#include "wx/zipstrm.h"
#include "../xml/tinyxml.h"
#include "savefile.hpp"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"
#include "../version.hpp"

SaveFile::SaveFile(wxString file)
{
	if(wxFileExists(file)!=true)
	{
		//Create AZP file if not exists
	wxFFileOutputStream out(file);
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
	zip.PutNextEntry(wxT("META-DATA")+ sep + wxT("VERSION.TXT"));
	txt << wxT("MinVersion: JUNO\n");
	txt << wxString::Format(wxT("<h1>Azpazeta Version Information</h1><h2>Version</h2><p>Major version: %d<br>Minor version: %d<br>Patch version: %d<br>Version name: %s<br>AZPScript Version: %d</p>"),AZPAZETA_VERSION_MAJOR,AZPAZETA_VERSION_MINOR,AZPAZETA_VERSION_PATCH,AZPAZETA_WX_NAME,AZPSCRIPT_VERSION);

	//Compiling options
        txt << wxT("<h2>Compile configuration</h2><p>Compiler: ");
	txt << wxString::FromUTF8(COMPILER_WX);
	txt << wxT("<br>CMake Version: ");
	txt << wxString::FromUTF8(CMAKE_WX_VERSION);
	txt << wxT("<br>Operating System: ");
	txt << wxString::FromUTF8(OS_WX);
	txt << wxT("<br>Processor: ");
	txt << wxString::FromUTF8(PROCESSOR_WX);
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
	TiXmlElement * element = new TiXmlElement( "Hello" );
	TiXmlText * text = new TiXmlText( "World" );
	element->LinkEndChild( text );
	doc.LinkEndChild( decl );
	doc.LinkEndChild( element );
	zip.PutNextEntry(wxT("AZP-DATA/main.xml"));
	TiXmlPrinter printer;
	printer.SetStreamPrinting ();
	doc.Accept (&printer);

	txt << wxString::FromUTF8(printer.CStr ());


	
	}


}
bool SaveFile::LoadAll()
{

}
bool SaveFile::SaveAll()
{

}
wxString SaveFile::Read(SAVEFILE_PARAMETERS parameter)
{




}
bool SaveFile::Set(SAVEFILE_PARAMETERS parameter, wxString value)
{


}
