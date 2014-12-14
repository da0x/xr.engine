/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.6 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_LoadingScreen.cpp,v 1.6 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#include "DGL_Main.h"
#include "DGL_Texture.h"
#include "DGL_LoadingScreen.h"
#include "DGL_Font.h"
#include "DGL_Color.h"
#include "DGL_Vertex.h"
#include "DGL_Fx.h"
#include "DSys_Window.h" // DSys::Window::SwapBuffers()



#define PROGRESS_STARTX			280
#define PROGRESS_ENDX			640 - PROGRESS_STARTX
#define PROGRESS_STARTY			175
#define PROGRESS_ENDY			180
#define PROGRESS_COLOR0			Color::ColorBlack()
#define PROGRESS_COLOR1			Color::ColorGreen()
#define PROGRESS_BACK_COLOR0	Color::ColorBlack()
#define PROGRESS_BACK_COLOR1	Color::ColorGray()
#define PROGRESS_COLOR_DIM		Color::ColorDim()
#define PROGRESS_BORDER_COLOR	Color::ColorGold()

namespace DGL {
	
	void LoadingScreen::Init()
	{
		this->percent = 0;
		this->tex.Build("textures/Loading.tga");
		this->font.Create("font");
		this->font.SetSize(0.75f);
		this->font.SetColor(DGL::Color::ColorGray());
		this->timer.Init();
	}

	void LoadingScreen::SetStage(int _percent, char *fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		vsprintf(this->text, fmt, ap);
		va_end(ap);
#ifndef _DEBUG
		while( this->percent++ < _percent )
		{
			this->PopFrame();
			::Sleep(30);
		}
#else // _DEBUG
		this->percent = _percent;
		this->PopFrame();
#endif
	}

    void LoadingScreen::PopFrame()
	{
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);	


		//
		// Text/info
		//
		this->font.Print(10, 20, this->text);

		//
		// Progress bar
		//

		// the progress background
		Draw2DRect(
			PROGRESS_STARTX,
			PROGRESS_STARTY,
			PROGRESS_ENDX,
			PROGRESS_ENDY,
			PROGRESS_BACK_COLOR0,
			PROGRESS_BACK_COLOR1);
		// this is the total progress bar
		Draw2DRect(
			PROGRESS_STARTX,
			PROGRESS_STARTY,
			Interpolate<int>(
			PROGRESS_STARTX,
			PROGRESS_ENDX,
			(float)(percent/100.0f)),
			PROGRESS_ENDY,
			PROGRESS_COLOR0,
			PROGRESS_COLOR1);

		// darw borders for the progress bar		
		MatrixOp::Ortho::Begin();
			glDisable(GL_TEXTURE_2D);
			glLineWidth(0.3f);
			glBegin(GL_LINE_STRIP);
				PROGRESS_BORDER_COLOR.MakeCurrent();
				glVertex2d( PROGRESS_STARTX,	PROGRESS_STARTY);
				PROGRESS_BORDER_COLOR.MakeCurrent();
				glVertex2d( PROGRESS_ENDX,		PROGRESS_STARTY);
				PROGRESS_BORDER_COLOR.MakeCurrent();
				glVertex2d( PROGRESS_ENDX,		PROGRESS_ENDY);
				PROGRESS_BORDER_COLOR.MakeCurrent();
				glVertex2d( PROGRESS_STARTX,	PROGRESS_ENDY);
				PROGRESS_BORDER_COLOR.MakeCurrent();
				glVertex2d( PROGRESS_STARTX,	PROGRESS_STARTY);
			glEnd();
			glLineWidth(1.0f);
			glEnable(GL_TEXTURE_2D);
		MatrixOp::Ortho::End();

		//
		// Loading image
		//

		Draw2DRect(320-50,240-25,100,50,tex);


		glPopAttrib();

		DSys::Window::SwapGLBuffers();
	}

	LoadingScreen::~LoadingScreen()
	{
		this->tex.Delete();
	}
}//namespace DGL