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
#include "gl.hpp"
//#include "GLES2/gl2.h"
#include "EGL/egl.h"

int args[]={WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

AZPGL::AZPGL(wxPanel* parent) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	gl=new wxGLContext(this);
	glEnable(GL_DEPTH_TEST);
}

void AZPGL::Resize(wxSizeEvent& event)
{

}
int AZPGL::getWidth()
{

}
int AZPGL::getHeight()
{

}
void AZPGL::Render(wxPaintEvent& event)
{

}
void AZPGL::AZPViewport(int a, int b, int c, int d)
{

}
void AZPGL::OnKey(wxKeyEvent& event)
{

}
