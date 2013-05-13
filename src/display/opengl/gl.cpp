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
#include "GL/glew.h"
#ifdef WIN32
#include <windows.h>
#endif
#include "gl.hpp"
#include <GL/gl.h>

#include "GL/glext.h"
#include "GL/glu.h"
#include "../../pathfinder/pathfinder.hpp"
#include "../../maploader/map.hpp"
#include "../../maploader/azpmap.hpp"
#include "shader.hpp"
#include "../../sprite/sprite.hpp"
#include "wx/filedlg.h"
#include "../../window/loader.hpp"
#include "../../log.hpp"
#include "../../azpscript/event.hpp"

extern wxString azppath;
extern AzpClient* client;

int args[]={WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

namespace Shader{
	extern int vPA;
	extern int tCA;
	extern int sU;

}
extern bool azplogo;
extern bool azpmosaic;
extern GLfloat mvMatrix[16];
int64_t* mapdata;
GLuint currenttexture;

AZPGL::AZPGL(wxPanel* parent, wxString azpmapuri) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	AzpLog("[INFO] Starting OpenGL Context",1);
	gl=new wxGLContext(this);
	
	
	wxInitAllImageHandlers();
	this->Connect(wxEVT_PAINT,wxPaintEventHandler(AZPGL::Render));
	this->Connect(wxEVT_SIZE,wxSizeEventHandler(AZPGL::Resize));
	this->Connect(wxEVT_KEY_UP, wxKeyEventHandler(AZPGL::OnKey));
	AzpLog("[OK] Defined main events",4);
	//wxLogMessage(azpmapuri);
	AZPSetup(0,0,0,0);

	/*
	AzpMap* azpmap=new AzpMap(azpmapuri);
	map=azpmap->GetData();
	wxLogMessage(map.inside.tile[1][1]);
	*/
	azpmap=new AzpMap(azpmapuri);
	AzpLog("[OK] Loaded map in TMX",4);
	eventm=new EventManager(azpmapuri);
	AzpLog("[OK] EventManager loaded",4);	
	

	imgpath=azppath+wxT("/media/");
	shaderEnabled=false;
	bufferEnabled=false;
	textureEnabled=false;
	glewEnabled=false;

	vadrixposx=0.0f;
	vadrixposy=0.0f;

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
	if(!glewEnabled)
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		glewEnabled=true;
	}
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
/* WORKS
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);
	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	int loc = glGetAttribLocation(program_shader, "vPosition");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	int loc2 = glGetAttribLocation(program_shader,"aTextureCoord");
	glVertexAttribPointer(loc2,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glUniform1i(glGetAttribLocation(program_shader,"uSampler"), 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleIndex);
	//glDrawElements(GL_TRIANGLES, 5, GL_UNSIGNED_INT, 0);
	
	glDrawArrays(GL_QUADS, 0, 4); //Square=glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	SwapBuffers();
*/

	if(azplogo)
	{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);

	mvMatrix[12]=0.0f;//x
	mvMatrix[13]=0.0f; //y
	mvMatrix[14]=0.0f;//z

	mvMatrix[0]=1.0f; //X-scale
	mvMatrix[5]=1.0f; //Y-Scale

	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glVertexAttribPointer(Shader::vPA, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glVertexAttribPointer(Shader::tCA,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glUniform1i(Shader::sU, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,triangleIndex);
	//glDrawElements(GL_TRIANGLES, 5, GL_UNSIGNED_INT, 0);
	AzpShader::SetMatrixUniforms();
	glDrawArrays(GL_QUADS, 0, 4); //Square=glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	SwapBuffers();
	}else if(azpmosaic)
	{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_shader);

	int fila;
	float xfila=-1.0f;
	int columna;
	float ycolumna=1.0f;
	for(columna=0;columna<21;columna++)
	{
	for(fila=0;fila<20;fila++)
	{
		mvMatrix[12]=xfila;//x
		mvMatrix[13]=ycolumna; //y
		mvMatrix[14]=0.0f;//z

		mvMatrix[0]=0.1f; //X-scale
		mvMatrix[5]=0.1f; //Y-Scale

	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glVertexAttribPointer(Shader::vPA, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//Select the Texture according the Data
	switch(azpmap->GetArrayData(fila,columna))
	{
		case 0:currenttexture=azptexture;break; //Azpazeta tile
		default:currenttexture=maintexture[azpmap->GetArrayData(fila,columna)];
	}
	

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glVertexAttribPointer(Shader::tCA,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, currenttexture);
	glUniform1i(Shader::sU, 0);


	AzpShader::SetMatrixUniforms();
	glDrawArrays(GL_QUADS, 0, 4);

	xfila+=0.1f;
	}
	xfila=-1.0f;
	ycolumna-=0.1f;
	}
	//SwapBuffers();

	//VADRIX
	//float actualposx=(float)((float)vadrixposx/10.0f);
	//float actualposy=(float)((float)vadrixposy/10.0f);	

		mvMatrix[12]=(float)vadrixposx/10.0f;
		mvMatrix[13]=(float)vadrixposy/10.0f;
		//wxMessageBox(wxString::Format(wxT("X Pos in FLOAT: %f\nY Pos in FLOAT: %f"),actualposx,actualposy)); CRASH!! Use it in Virus...
		//printf("X Pos in float: %f\nY Pos in float: %f\n",(float)vadrixposx/10.0f,(float)vadrixposy/10.0f);
		mvMatrix[0]=0.1f; //X-scale
		mvMatrix[5]=0.1f; //Y-Scale



	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glVertexAttribPointer(Shader::vPA,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glVertexAttribPointer(Shader::tCA,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vadrixtexture[0]);
	glUniform1i(Shader::sU, 0);


	AzpShader::SetMatrixUniforms();
	glDrawArrays(GL_QUADS, 0, 4);
	
	SwapBuffers();

	//VADRIX
	//SwapBuffers();
	//Vadrix ahora no tiene Alpha Channel, asi pues se cargan imagenes con fondo
  	/* SOLO FUNCIONA SI VADRIX TIENE ALPHA CHANNEL. La funcion GetData no devuelve Alpha Channel

	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		mvMatrix[12]=0.2f;//x
		mvMatrix[13]=0.2f; //y
		mvMatrix[0]=0.1f; //X-scale
		mvMatrix[5]=0.1f; //Y-Scale

	glBindBuffer(GL_ARRAY_BUFFER,triangleBuffer);
	glVertexAttribPointer(Shader::vPA, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,triangleTexture);
	glVertexAttribPointer(Shader::tCA,2,GL_FLOAT,GL_FALSE,0,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vadrixtexture[0]);
	glUniform1i(Shader::sU, 0);


	AzpShader::SetMatrixUniforms();
	glDrawArrays(GL_QUADS, 0, 4);
	 
   glDisable(GL_BLEND);
	//Draw
	SwapBuffers();
	*/
	



	}else
	{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glViewport(0, 0, getHeight(), getHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	/*std::string openglabout;
	openglabout.append((const char*)glGetString(GL_VERSION));
	openglabout.append((const char*)glGetString(GL_VENDOR));
	openglabout.append((const char*)glGetString(GL_RENDERER));
	openglabout.append((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	openglabout.append((const char*)glGetString(GL_EXTENSIONS));
	SwapBuffers();

	wxMessageBox(wxString::FromUTF8(openglabout.c_str()));*/
	}

	


}
void AZPGL::AZPSetup(int a, int b, int c, int d)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f,0.0f,0.0f,1.0f);
}
void AZPGL::OnKey(wxKeyEvent& event)
{
	if(client==NULL)
	{
		wxMessageBox(_("Please, start a new game, load a saved game or play multiplayer. Currently nothing is selected"),_("Divel Network"),wxICON_WARNING|wxOK);
		return;

	}
	
	switch(event.GetKeyCode())
	{
		case WXK_ESCAPE:wxExit();break;
		case WXK_TAB:{
		wxFileDialog* screenshotsaver=new wxFileDialog(this,_("Save the screenshot"),wxT(""),wxT(""),wxT("PNG files (*.png)|*.png"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		if(screenshotsaver->ShowModal()==wxID_OK)
		{
		//Take a screenshot
		Screenshot* photo=new Screenshot(this,screenshotsaver->GetPath());
		}
		}break;
		case WXK_LEFT:{
			vadrixside=1;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx-1+10,vadrixposy+10,azpmap->GetArrayData(vadrixposx-1+10,vadrixposy*-1+10)))
			{
				vadrixposx-=1;
				//Execute Events TODO
				//printf("Event of: %d:%d\n",vadrixposx+10,vadrixposy*-1+10);
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();

			}
		}break;
		case WXK_UP:{
			vadrixside=3;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx+10,vadrixposy+1+10,azpmap->GetArrayData(vadrixposx+10,vadrixposy*-1+10-1)))
			{
				vadrixposy+=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}
		}break;
		case WXK_RIGHT:{
			vadrixside=2;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx+1+10,vadrixposy+10,azpmap->GetArrayData(vadrixposx+10+1,vadrixposy*-1+10)))
			{
				vadrixposx+=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}
		}break;
		case WXK_DOWN:{
			vadrixside=0;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposy+10,vadrixposy-1+10,azpmap->GetArrayData(vadrixposx+10,vadrixposy*-1+10+1)))
			{
				vadrixposy-=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}
		}break;
		case 'W':{
			vadrixside=3;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx+10,vadrixposy+1+10,azpmap->GetArrayData(vadrixposx+10,vadrixposy*-1+10-1)))
			{
				vadrixposy+=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}

		}break;
		case 'A':{
			vadrixside=1;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx-1+10,vadrixposy+10,azpmap->GetArrayData(vadrixposx+10-1,vadrixposy*-1+10)))
			{
				vadrixposx-=1;
				//Execute Events TODO
				//printf("Event of: %d:%d\n",vadrixposx+10,vadrixposy*-1+10);
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();

			}

		}break;
		case 'S':{
			vadrixside=0;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposy+10,vadrixposy-1+10,azpmap->GetArrayData(vadrixposx+10,vadrixposy*-1+10+1)))
			{
				vadrixposy-=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}

		}break;
		case 'D':{
			vadrixside=2;
			//Comunicate with Server TODO
			if(client->RequestMove(vadrixposx+1+10,vadrixposy+10,azpmap->GetArrayData(vadrixposx+10+1,vadrixposy*-1+10)))
			{
				vadrixposx+=1;
				//Execute Events TODO
				eventm->Execute(vadrixposx+10,vadrixposy*-1+10);
				//Refresh TODO
				Refresh();
			}

		}break;
		default:{
				/*wxYield();
				Refresh();
				wxYield();
				Update();*/
		}
	}
		
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
          0.0, 1.0,
          1.0, 1.0,
          1.0, 0.0,
          0.0, 0.0
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
	AzpLog("[INFO] Started compiling shaders",1);
	vertex_shader=AzpShader::LoadShader(azppath+wxT("/shaders/vertex.vs"),GL_VERTEX_SHADER);
	fragment_shader=AzpShader::LoadShader(azppath+wxT("/shaders/fragment.fs"),GL_FRAGMENT_SHADER);
	program_shader=AzpShader::CreateProgram(vertex_shader,fragment_shader);
	AzpLog("[OK] Shaders created",4);
	
}
void AZPGL::AZPTexture()
{
	AzpLog("[INFO] Starting loading textures",1);
	WindowLoader* winl=new WindowLoader();

	wxImage azpazeta_img(azppath+_("/media/azpazeta.png"),wxBITMAP_TYPE_PNG);
	glGenTextures(1, &azptexture);
	glBindTexture(GL_TEXTURE_2D, azptexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, azpazeta_img.GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	int test;
	for(test=0;test<750;test++)
		winl->Next();
	winl->Finish();

	//VADRIX -- No hacer transparente, sino del fondo del lugar (bosque o desierto)

	SpriteLoader* vadrixsprite=new SpriteLoader(azppath+wxT("/media/vadrixmain.png"),64);
	glGenTextures(1,&vadrixtexture[0]);
	glBindTexture(GL_TEXTURE_2D, vadrixtexture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, vadrixsprite->GetSprite(1).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Other sides of Vadrix TODO

	delete vadrixsprite;

	//BLUEANDRED

	SpriteLoader* dualsprite=new SpriteLoader(azppath+wxT("/media/dualsprite.png"),64);

	glGenTextures(1, &maintexture[1]);
	glBindTexture(GL_TEXTURE_2D, maintexture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, dualsprite->GetSprite(0).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[2]);
	glBindTexture(GL_TEXTURE_2D, maintexture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, dualsprite->GetSprite(1).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	delete dualsprite;

	//HOUSE1	

	SpriteLoader* housesprite=new SpriteLoader(azppath+wxT("/media/housemain.png"),64);
	
	glGenTextures(1, &maintexture[4]);
	glBindTexture(GL_TEXTURE_2D, maintexture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(0).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[5]);
	glBindTexture(GL_TEXTURE_2D, maintexture[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(1).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[6]);
	glBindTexture(GL_TEXTURE_2D, maintexture[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(2).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[7]);
	glBindTexture(GL_TEXTURE_2D, maintexture[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(3).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[8]);
	glBindTexture(GL_TEXTURE_2D, maintexture[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(4).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[9]);
	glBindTexture(GL_TEXTURE_2D, maintexture[9]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(5).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[10]);
	glBindTexture(GL_TEXTURE_2D, maintexture[10]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(6).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[11]);
	glBindTexture(GL_TEXTURE_2D, maintexture[11]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(7).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &maintexture[12]);
	glBindTexture(GL_TEXTURE_2D, maintexture[12]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, housesprite->GetSprite(8).GetData());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	wxMessageBox(wxString::Format(wxT("%d"),housesprite->GetNumbers()));
	AzpLog("[OK] Textures loaded",4);
	
	delete housesprite;


	
}
#endif
