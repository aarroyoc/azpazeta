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
#ifndef CORE_HPP
#define CORE_HPP
typedef enum{
azpCLIENT_SINGLE,
azpCLIENT_MULTI,
azpCLIENT_LOAD
}azpCLIENT_STATE;

class AzpClient
{
	public:
		AzpClient(azpCLIENT_STATE mode=azpCLIENT_SINGLE,wxString ip=wxT("::1"),bool ipv6=true);
		static float Version();
		void Connect();
		void Disconnect();
	private:
		int server;
		wxProcess* process;
};
#endif
