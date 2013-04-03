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

namespace Shader{
	int vPA;
	int tCA;
	int sU;
	int pMatrix;
	int mvMatrix;

}
GLfloat mvMatrix[]={
	1.0f,0.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f
	};



GLint AzpShader::LoadShader(wxString file, GLenum type)
{
	wxFFile shadersource(file,wxT("r"));
	wxString shaderstring;
	shaderstring.Clear();
	shadersource.ReadAll(&shaderstring);
	const GLchar* shaderSrc=shaderstring.mb_str();
	
	
	const GLchar* vShaderStr=
	"attribute vec2 aTextureCoord;\n"
	"attribute vec3 vPosition; \n"
	"varying vec2 vTextureCoord;\n"
	"uniform mat4 uMVMatrix;\n"
	"mat4 igual=mat4(\n"
	"1.0,0.0,0.0,0.0,\n"
	"0.0,1.0,0.0,0.0,\n"
	"0.0,0.0,1.0,0.0,\n"
	"0.0,0.0,0.0,1.0);\n"
	"void main() \n"
	"{ \n"
	" gl_Position = uMVMatrix * vec4(vPosition, 1.0); \n"
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
	"  //gl_FragColor = vec4(0.0,0.0,1.0,1.0);\n"
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
			log.Append(wxString::FromUTF8(vShaderStr));
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
	/* glBindAttribLocation(program_shader, 0, "vPosition"); */
	//glBindAttribLocation(program_shader,0,"aTextureCoord");
	// Link the program
	glLinkProgram(program_shader);


        Shader::vPA = glGetAttribLocation(program_shader, "vPosition");
        glEnableVertexAttribArray(Shader::vPA);

        Shader::tCA = glGetAttribLocation(program_shader, "aTextureCoord");
        glEnableVertexAttribArray(Shader::tCA);

	Shader::mvMatrix=glGetUniformLocation(program_shader,"uMVMatrix");
	

        Shader::sU = glGetUniformLocation(program_shader, "uSampler");
	
	return program_shader;
}
void AzpShader::SetMatrixUniforms()
{
	glUniformMatrix4fv(Shader::mvMatrix,1,false,mvMatrix);
	GLenum glerror=glGetError();
		if(glerror!=GL_NO_ERROR)
        		fprintf(stderr, "GL error: %x\n", glerror);
	
	
}
void AzpShader::PushMatrix(GLfloat* matrix)
{
	
}
GLfloat* AzpShader::PopMatrix()
{

}

