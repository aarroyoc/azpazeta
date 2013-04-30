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

#include "server.hpp"
#include "server_command.hpp"

extern SOCKET sock_client[100];
int xpos[100];
int ypos[100];

void LoopProcess(int64_t me)
{
char receivemessage[2048];
char* commandpart;
char response[2048];
	while(true)
	{
		recv(sock_client[me],receivemessage,2048,0);
		commandpart=strtok(receivemessage,"]");
		if(strcmp(commandpart,"[REQUEST")==0)
		{
			//Request Move
			commandpart=strtok(NULL,"|");
			xpos[me]=atoi(commandpart);
			commandpart=strtok(NULL,"|");
			ypos[me]=atoi(commandpart);
			snprintf(response,2048,"TRUE");
			send(sock_client[me],response,2048,0);


		}
		if(strcmp(commandpart,"[GET")==0)
		{
			commandpart=strtok(NULL,"]");
			if(strcmp(commandpart,"USER-NUMBER")==0)
			{
				snprintf(response,2048,"%lld",(long long)me);
				send(sock_client[me],response,2048,0);

			}			


		}
		if(strcmp(commandpart,"[EXIT")==0)
		{
	
			return;

		}




	}

}
