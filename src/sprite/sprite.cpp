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
#include "wx/wx.h"
#include "wx/dcclient.h"
#include "wx/window.h"
#include "wx/dcmemory.h"
#include "wx/image.h"
#include "sprite.hpp"
//Los Sprites se leen en línea [SIZE-SIZE-SIZE]

SpriteLoader::SpriteLoader(wxString filename, int size)
{
	/*
	Works*/
	wxImage image(filename,wxBITMAP_TYPE_PNG);
	
	wxImage copy;
	for(numbers=0;numbers*size<image.GetWidth();numbers++)
	{
		//copy=image;
		//sprites[numbers]=image.Size(wxSize(size,size),wxPoint(-1*size*numbers,0),0,120,120);
		//ImageWindow* imw=new ImageWindow(sprites[numbers]);
		//imw->ShowModal();
		sprites[numbers]=image.GetSubImage(wxRect(size*numbers,0,size,size));
		//ImageWindow* imw=new ImageWindow(sprites[numbers]);
		//imw->ShowModal();

	}
	/*
	Works, but its a lot of RAM (I think)	
	wxBitmap img(filename,wxBITMAP_TYPE_PNG);
	wxMemoryDC imagedc;
	imagedc.SelectObject(img);
	imagedc.DrawText(wxT("TEST OF SPRITELOADER"), 1,1);
	img.SaveFile(filename,wxBITMAP_TYPE_PNG);*/
}
int SpriteLoader::GetNumbers()
{
	return numbers;
}
wxImage SpriteLoader::GetSprite(int number)
{
	return sprites[number];
}
/*
Screenshot class. Save a photo of the moment*/
Screenshot::Screenshot(wxWindow* win, wxString filename)
{
	wxWindowDC* windc=new wxWindowDC(win);
	wxMemoryDC memdc;
	wxSize winsize=win->GetSize();
	wxBitmap screenshot(winsize.GetWidth(),winsize.GetHeight());
	memdc.SelectObject(screenshot);
	memdc.Blit(wxPoint(0,0),winsize,windc,wxPoint(0,0));
	memdc.DrawText(wxT("Azpazeta JUNO 2.0"),1,1);
	wxDateTime now = wxDateTime::Now();
	memdc.DrawText(now.Format(wxT("%c"), wxDateTime::CET),wxPoint(150,0));


	screenshot.SaveFile(filename,wxBITMAP_TYPE_PNG);


}
ImageWindow::ImageWindow(wxImage image) : wxDialog (NULL,wxID_ANY,_("Azpazeta Image Viewer"),wxDefaultPosition,wxSize(800,800))
{
	wxBitmap bmp(image);
	wxStaticBitmap* bitmap=new wxStaticBitmap(this,wxID_ANY,bmp);
}
