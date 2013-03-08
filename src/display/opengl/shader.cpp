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
#include <iostream>
#include "GL/gl.h"
#include "GL/glext.h"
#include "shader.hpp"
#include "wx/ffile.h"
/* I don't know way but I need add this in GCC -DGL_GLEXT_PROTOTYPES */


GLint AzpShader::LoadShader(wxString file, GLenum type)
{
	wxFFile shadersource(file,wxT("r"));
	wxString shaderstring;
	shaderstring.Clear();
	shadersource.ReadAll(&shaderstring);
	const GLchar* shaderSrc=shaderstring.mb_str();
	
	
	const GLchar* vShaderStr=
	"attribute vec2 aTextureCoord;\n"
	"attribute vec4 vPosition; \n"
	"varying vec2 vTextureCoord;\n"
	"void main() \n"
	"{ \n"
	" gl_Position = vPosition; \n"
	"vTextureCoord = aTextureCoord;\n"
	"} \n";
	const GLchar* fShaderStr=
	"#ifdef GL_ES\n"
	"precision mediump float; \n"
	"#endif\n"
	"varying vec2 vTextureCoord;\n"
	"uniform sampler2D uSampler;\n"
	"void main() \n"
	"{ \n"
	" gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t)); \n"
	"} \n";
	
	GLuint shader;	
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
	if(shader == 0)
		wxLogError(_("Error creating shaders"));
	// Load the shader source
	glShaderSource(shader, 1, (type==GL_VERTEX_SHADER)?&vShaderStr : &fShaderStr, NULL);
	// Compile the shader
	glCompileShader(shader);
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
 	if(!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char infoLog[2048];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			wxString log=_("Error compiling shader:\n");
			log.Append(wxString::FromUTF8(infoLog));
			log.Append(_("\nFile: "));
			log.Append(shaderstring);
			wxLogError(log);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
GLint AzpShader::CreateProgram(GLint vertex, GLint fragment)
{
	GLint program_shader=glCreateProgram();
	if(program_shader == 0){
		wxLogError(wxString::Format(_("Error while creating shader program in %s"),(char*)glGetString(GL_VERSION)));
		GLenum glerror=glGetError();
		if(glerror!=GL_NO_ERROR)
        		fprintf(stderr, "GL error: %x\n", glerror);
	}
		
	glAttachShader(program_shader, vertex);
	glAttachShader(program_shader, fragment);
	// Bind vPosition to attribute 0
	glBindAttribLocation(program_shader, 0, "vPosition");
	// Link the program
	glLinkProgram(program_shader);
	return program_shader;
}
