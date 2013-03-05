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
//#include "EGL/egl.h"
//#include "GLES2/gl2.h"
#include "gl.hpp"
#include "GL/glu.h"
#include "../../pathfinder/pathfinder.hpp"

extern wxString azppath;

int args[]={WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

AZPGL::AZPGL(wxPanel* parent) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	gl=new wxGLContext(this);
	
	wxInitAllImageHandlers();
	this->Connect(wxEVT_PAINT,wxPaintEventHandler(AZPGL::Render));
	this->Connect(wxEVT_SIZE,wxSizeEventHandler(AZPGL::Resize));
	
}

void AZPGL::Resize(wxSizeEvent& event)
{
	Refresh();
}
int AZPGL::getWidth()
{
	return GetSize().x;
}
int AZPGL::getHeight()
{
	return GetSize().y;
}
void AZPGL::Render(wxPaintEvent& event)
{

	if(!IsShown()) return;
    
    wxGLCanvas::SetCurrent(*gl);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // ------------- draw some 2D ----------------
    AZPViewport(0,0,getWidth()/2, getHeight());
    glLoadIdentity();
	
    // white background
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(getWidth(),0,0);
    glVertex3f(getWidth(),getHeight(),0);
    glVertex3f(0,getHeight(),0);
    glEnd();

	glEnable(GL_TEXTURE_2D);

	wxImage imagen(azppath+wxT("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen.GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



    // AZP square
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);glVertex3f(getWidth()/8, getHeight()/3, 0);
    glTexCoord2f(1, 0);glVertex3f(getWidth()*3/8, getHeight()/3, 0);
    glTexCoord2f(1, 1);glVertex3f(getWidth()*3/8, getHeight()*2/3, 0);
    glTexCoord2f(0, 1);glVertex3f(getWidth()/8, getHeight()*2/3, 0);
    glEnd();
	glFlush();
	SwapBuffers();
}
void AZPGL::AZPViewport(int a, int b, int c, int d)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(a, b, c-a, d-b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(a, c, d, b);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void AZPGL::OnKey(wxKeyEvent& event)
{

}
