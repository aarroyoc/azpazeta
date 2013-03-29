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
#include "wx/process.h"
#include "wx/utils.h"
#include "wx/wx.h"

#include "core.hpp"
#include "server.hpp"
extern wxString azppath;
/*
Client of Azpazeta Server 
*/
class ServerProcess : public wxProcess
{
public:
    ServerProcess() : wxProcess()
    {
        
    }

    // instead of overriding this virtual function we might as well process the
    // event from it in the frame class - this might be more convenient in some
    // cases
    virtual void OnTerminate(int pid, int status)
	{
		wxMessageBox(_("Server fails!"),_("Azpazeta"),wxICON_ERROR|wxOK);	
	}
};


float AzpClient::Version()
{	
	return 2.0;
}
AzpClient::AzpClient(azpCLIENT_STATE mode,wxString ip,bool ipv6)
{
/* Creating the server if is needed */
if(mode==azpCLIENT_SINGLE)
{
	process=new ServerProcess();
	/*process=new wxProcess();*/
	process->Open(azppath+wxT("/AZPSERVER ipv6"),wxEXEC_ASYNC);
	wxMilliSleep(1000);
	
}else{
process=NULL;

}
/* Opening connection to Server */

struct sockaddr_in  sockaddr_ipv4;
struct sockaddr_in6 sockaddr_ipv6;

#ifdef WIN32



#else
if(!ipv6)
{
                printf("AF_INET (IPv4)\n");
		server = socket (AF_INET, SOCK_STREAM, 0);

		if (server == -1)
		{
    		printf ("Error\n");
		} 
		sockaddr_ipv4.sin_family = AF_INET;
		sockaddr_ipv4.sin_port = htons(6996);
		inet_pton(AF_INET, ip.mb_str(), &(sockaddr_ipv4.sin_addr));
	
		if (connect (server, (struct sockaddr *)&sockaddr_ipv4,sizeof (sockaddr_ipv4)) == -1)
		{
		    printf ("Error\n");
		} 	

}else{

                printf("AF_INET6 (IPv6)\n");
		server = socket (AF_INET6, SOCK_STREAM, 0);

		if (server == -1)
		{
    		printf ("Error\n");
		} 
		sockaddr_ipv6.sin6_family = AF_INET6;
		sockaddr_ipv6.sin6_port = htons(6996);
		inet_pton(AF_INET6, ip.mb_str(), &(sockaddr_ipv6.sin6_addr));
	
		if (connect (server, (struct sockaddr *)&sockaddr_ipv6,sizeof (sockaddr_ipv6)) == -1)
		{
		    printf ("Error\n");
		}
}

#endif
}
void AzpClient::Connect()
{
	char buffer[1024];
	recv(server, buffer, 1024, 0);
	wxMessageBox(wxString::FromUTF8(buffer),wxT("Divel Network"));
	send(server,buffer,1024,0);
	recv(server,buffer,1024,0);
	wxMessageBox(wxString::FromUTF8(buffer),wxT("Divel Network"));	

}
void AzpClient::Disconnect()
{
	if(process!=NULL)
	{
		delete process;
	}
}
