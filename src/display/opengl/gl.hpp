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
/* OpenGL ES 2.0 Implementation of Azpazeta Display - This is the version with most performance */

#include "wx/wx.h"
#include "wx/glcanvas.h"

class AZPGL : public wxGLCanvas
{
	private:
		wxGLContext* gl;
		
	public:
		AZPGL(wxPanel* parent);
		void Resize(wxSizeEvent& event);
		int getWidth();
		int getHeight();
		void Render(wxPaintEvent& event);
		void AZPViewport(int a, int b, int c, int d);
		void OnKey(wxKeyEvent& event);



};
