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

#include <stdio.h>
#include "server.hpp"
#include "server_command.hpp"

extern SOCKET sock_client[100];
int xpos[100];
int ypos[100];
int building;

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
			commandpart=strtok(NULL,"|");
			building=atoi(commandpart);
			if(xpos[me]>20 || xpos[me]<0 || ypos[me]>20 || ypos[me]<1) //21,0,21,0
			{
				sprintf(response,"MIGHT");
				printf("Changing map...");
			}
			else if(CheckBuilding(building)==false){
				//printf("YPOS[ME]: %d\t",ypos[me]);
				sprintf(response,"FALSE");

			}
			else
			{
				sprintf(response,"TRUE");
			}
			send(sock_client[me],response,2048,0);


		}
		if(strcmp(commandpart,"[GET")==0)
		{
			commandpart=strtok(NULL,"]");
			if(strcmp(commandpart,"USER-NUMBER")==0)
			{
				sprintf(response,"%lld",(long long)me);
				send(sock_client[me],response,2048,0);

			}			


		}
		if(strcmp(commandpart,"[EXIT")==0)
		{
	
			return;

		}




	}

}
bool CheckBuilding(int buildingcode)
{
	printf("BuildingCode: %d\n",buildingcode);
	bool result=false;		
	//Whitelist
	switch(buildingcode)
	{
		case 1: //Green
		case 2: //Red
		case 4: //Green
		case 23: //Bridge 
		case 24: //Bridge
		case 54: //Enter to the cave
		case 66: //Enter to the cave
		case 75:result=true;break; //Green


	
	}
	return result;

}
