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
/**
* @file gl.hpp
* @brief OpenGL ES 2 Implementation of Azpazeta Display
* @author Adrián Arroyo Calle
* @date 1/03/2013
*/

#include <GL/glew.h>
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "../../maploader/map.hpp"
#include "../../maploader/azpmap.hpp"
#include "../../azpscript/event.hpp"
#include "../../core/core.hpp"

/**
 * @class AZPGL
 * @brief Implementation of Azpazeta Display in OpenGL ES 2
 */


class AZPGL : public wxGLCanvas
{
	private:
		wxGLContext* gl;
		AzpMapData map;
		wxString imgpath;
		float xDesp;
		float yDesp;
		GLint vertex_shader;
		GLint fragment_shader;
		GLint program_shader;
		bool shaderEnabled;
		bool bufferEnabled;
		bool textureEnabled;
		bool glewEnabled;
		unsigned int triangleBuffer;
		unsigned int triangleTexture;
		unsigned int triangleIndex;
		GLuint azptexture;
		GLuint maintexture[120];
		GLuint vadrixtexture[4];
		AzpMap* azpmap;
		EventManager* eventm;
		int vadrixside; //0=Down 1=Left 2=Right 3=Up
		int vadrixposx;
		int vadrixposy;
		
	public:
		AZPGL(wxPanel* parent,wxString azpmapuri);
		void Resize(wxSizeEvent& event);
		int getWidth();
		int getHeight();
		void Render(wxPaintEvent& event);
		void AZPSetup(int a, int b, int c, int d);
		void OnKey(wxKeyEvent& event);
		void AZPBuffer();
		void AZPShader();
		void AZPTexture();



};
