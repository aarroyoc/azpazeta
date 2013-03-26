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
#include "../../maploader/map.hpp"
#include "../../maploader/azpmap.hpp"
#include "shader.hpp"

extern wxString azppath;

int args[]={WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};


AZPGL::AZPGL(wxPanel* parent, wxString azpmapuri) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	gl=new wxGLContext(this);
	
	wxInitAllImageHandlers();
	this->Connect(wxEVT_PAINT,wxPaintEventHandler(AZPGL::Render));
	this->Connect(wxEVT_SIZE,wxSizeEventHandler(AZPGL::Resize));
	this->Connect(wxEVT_KEY_UP, wxKeyEventHandler(AZPGL::OnKey));
	//wxLogMessage(azpmapuri);
	AZPSetup(0,0,0,0);

	AzpMap* azpmap=new AzpMap(azpmapuri);
	map=azpmap->GetData();
	wxLogMessage(map.inside.tile[1][1]);
	imgpath=azppath+wxT("/media/");
	shaderEnabled=false;
	bufferEnabled=false;
	textureEnabled=false;

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
#ifdef OPENGL_BEGIN_END
//OpenGL 1 Implementation -- Too slow on virtual machine
void AZPGL::Render(wxPaintEvent& event)
{

	if(!IsShown()) return;
    
    wxGLCanvas::SetCurrent(*gl);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // ------------- draw some 2D ----------------
    AZPViewport(0,0,getWidth()/2, getHeight());
    glLoadIdentity();
	
   /* // white background
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(getWidth(),0,0);
    glVertex3f(getWidth(),getHeight(),0);
    glVertex3f(0,getHeight(),0);
    glEnd();*/

	//Load textures
	glEnable(GL_TEXTURE_2D);

	wxImage imagen(azppath+wxT("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen.GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



    // AZP square old way
    /*glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);glVertex3f(getWidth()/8, getHeight()/3, 0);
    glTexCoord2f(1, 0);glVertex3f(getWidth()*3/8, getHeight()/3, 0);
    glTexCoord2f(1, 1);glVertex3f(getWidth()*3/8, getHeight()*2/3, 0);
    glTexCoord2f(0, 1);glVertex3f(getWidth()/8, getHeight()*2/3, 0);
    glEnd();*/


	/* New Viewport
	glColor4f(1,1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);glVertex3f(0,0,0);
		glTexCoord2f(0,0);glVertex3f(0,20,0);
		glTexCoord2f(1,0);glVertex3f(20,20,0);
		glTexCoord2f(1,1);glVertex3f(20,0,0);
	glEnd();
	*/
	//Cargar mapa
	AzpMap* azpmap=new AzpMap(azppath+wxT("/maps/core/start.xml"));
	AzpMapData map=azpmap->GetData();
	int lecturaX;
	int lecturaY;
	int factor=10;
	bool defaultImage=true;
	wxImage defImage(azppath+wxT("/media/green.png"));
	for(lecturaX=0;lecturaX<99;lecturaX++)
	{
		for(lecturaY=0; lecturaY<99;lecturaY++)
		{
			wxString tile_image;
			if(map.inside.tile[lecturaX][lecturaY].IsEmpty())
			{
				defaultImage=true;

			}else{
			
				defaultImage=false;
				tile_image=azppath+wxT("/maps/core/")+map.inside.tile[lecturaX][lecturaY];
			}
			
			if(defaultImage)
			{
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, defImage.GetData());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			}else{
			wxImage imagen(tile_image,wxBITMAP_TYPE_PNG);
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen.GetData());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			glColor4f(1,1,1,1);
			glBegin(GL_QUADS);
				glTexCoord2f(0,1);glVertex3f(factor*lecturaX-100,factor*lecturaY-100,0);
				glTexCoord2f(0,0);glVertex3f(factor*lecturaX-100,factor*lecturaY+factor-100,0);
				glTexCoord2f(1,0);glVertex3f(factor*lecturaX+factor-100,factor*lecturaY+factor-100,0);
				glTexCoord2f(1,1);glVertex3f(factor*lecturaX+factor-100,factor*lecturaY-100,0);
			glEnd();
			
		}
		

	}
	//Dibujar jugador
	wxImage imagena(azppath+wxT("/maps/core/red.png"),wxBITMAP_TYPE_PNG);
	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, imagena.GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1);glVertex3f(factor*xDesp-100,factor*yDesp-100,0);
		glTexCoord2f(0,0);glVertex3f(factor*xDesp-100,factor*yDesp+factor-100,0);
		glTexCoord2f(1,0);glVertex3f(factor*xDesp+factor-100,factor*yDesp+factor-100,0);
		glTexCoord2f(1,1);glVertex3f(factor*xDesp+factor-100,factor*yDesp-100,0);

	glEnd();
	
	
    

	glFlush();
	SwapBuffers();


}
void AZPGL::AZPViewport(int a, int b, int c, int d)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    //glViewport(a, b,(16*getHeight())/9 , getHeight()); //glViewport x,y, width, height // 16:9
    glViewport(a,b,getHeight(),getHeight()); //glViewport 1:1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //gluOrtho2D(a, c, d, b);
    glOrtho(-100.0f,100.0f,-100.0f,100.0f,100.0f,-100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void AZPGL::OnKey(wxKeyEvent& event)
{
	switch(event.GetKeyCode())
	{
		case WXK_ESCAPE:{
			int salir=wxMessageBox(_("Do you want to exit?"),wxT("Azpazeta"),wxICON_QUESTION|wxYES_NO);
        		if(salir==wxYES){
            			this->Destroy();
            			wxExit();
			}
		}
		case WXK_LEFT:{
			xDesp++;
			Refresh();
		}
	}
}
#else
//OpenGL ES 2 Implementation
void AZPGL::Render(wxPaintEvent& event)
{
	if(!IsShown()) return;
    
	wxGLCanvas::SetCurrent(*gl);
	wxPaintDC(this);
	
	if(!shaderEnabled)
	{
		AZPShader();
		shaderEnabled=true;
	}
	if(!bufferEnabled)
	{
		AZPBuffer();
		bufferEnabled=true;
	}
	if(!textureEnabled)
	{
		AZPTexture();
		textureEnabled=true;
	}



	/* Using Matrices vertices like vVertices
	// Set the viewport
	glViewport(0, 0, getWidth(), getHeight());
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	glUseProgram(program_shader);
	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SwapBuffers();
	*/
	/* Using VBO */
	/* Works
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);
	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	int loc = glGetAttribLocation(program_shader, "vPosition");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SwapBuffers();*/

/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
   

	glViewport(0, 0, getHeight(), getHeight());
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);
	int loc =glGetAttribLocation(program_shader, "vPosition");
	int loc2=glGetAttribLocation(program_shader,"aTextureCoord");
	int loc3=glGetAttribLocation(program_shader,"uSampler");


	//Vertex
	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);




	//Textures
	
	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glVertexAttribPointer(loc2,2,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glUniform1i(loc3, 0);
	





	//Index

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleIndex);
	glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_INT,0);	
	SwapBuffers();


	GLenum glerror=glGetError();
	if(glerror!=GL_NO_ERROR)
        	fprintf(stderr, "GL error: %x\n", glerror);
	else
		fprintf(stderr,"GL not error: %x\n", glerror);
	
	//glDrawArrays(GL_TRIANGLES, 0, 30);
	//SwapBuffers();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
*/
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);
	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	int loc = glGetAttribLocation(program_shader, "vPosition");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	int loc2 = glGetAttribLocation(program_shader,"vTextureCoord");
	glVertexAttribPointer(loc2,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glUniform1i(glGetAttribLocation(program_shader,"uSampler"), 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleIndex);
	//glDrawElements(GL_TRIANGLES, 5, GL_UNSIGNED_INT, 0);
	
	glDrawArrays(GL_QUADS, 0, 4); //Square=glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	SwapBuffers();

	


}
void AZPGL::AZPSetup(int a, int b, int c, int d)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f,0.0f,0.0f,1.0f);
}
void AZPGL::OnKey(wxKeyEvent& event)
{

}
void AZPGL::AZPBuffer()
{
	//Primero buffer de verices
	//Many squares 30 Vertex
	//0--1--2--3--4
	//5--6--7--8--9
	/*GLfloat vVertices[] = {
	0.0f, 0.0f, 0.0f,
	0.1f, 0.0f, 0.0f,
	0.2f, 0.0f, 0.0f,
	0.3f, 0.0f, 0.0f,
	0.4f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.1f, 0.5f, 0.0f,
	0.2f, 0.5f, 0.0f,
	0.3f, 0.5f, 0.0f,
	0.4f, 0.5f, 0.0f,

	};*/
	GLfloat vVertices[]={
            // Front face
            -0.5, -0.5,  1.0,
             0.5, -0.5,  1.0,
             0.5,  0.5,  1.0,
            -0.5,  0.5,  1.0};
	glGenBuffers(1,&triangleBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
	//Luego buffer de textura
	GLfloat texCoords[] = {
          // Front face
          0.0, 0.0,
          1.0, 0.0,
          1.0, 1.0,
          0.0, 1.0
        };
	glGenBuffers(1,&triangleTexture);
	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	//Luego buffer de INDEX
	//8x3=24
	GLfloat index[]={
            0, 1, 2,      0, 2, 3    // Front face
	};
	glGenBuffers(1,&triangleIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index,GL_STATIC_DRAW);
	
}
void AZPGL::AZPShader()
{
	vertex_shader=AzpShader::LoadShader(azppath+wxT("/shaders/vertex.vs"),GL_VERTEX_SHADER);
	fragment_shader=AzpShader::LoadShader(azppath+wxT("/shaders/fragment.fs"),GL_FRAGMENT_SHADER);
	program_shader=AzpShader::CreateProgram(vertex_shader,fragment_shader);
	
}
void AZPGL::AZPTexture()
{
	wxImage azpazeta_img(azppath+_("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	glGenTextures(1, &azptexture);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, azpazeta_img.GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
}
#endif
