/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Main.cpp,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


/*
 TODO List:
- Execute command line
*/

#include <stdarg.h>
#include "DSys.H"
#include "DSys_ConfigDialog.h"
#include <gl/gl.h>
#include <gl/glu.h>

namespace DSys
{
	void SystemInitialize( std::string commandArg)
	{
		// Todo: execute command line
		DSys::InitConsole();
	}

	void SystemStart()
	{
		// default.cfg MUST exist
		if(! D_FileExist( "user/default.cfg" ) )
			throw Daher::Exception("Could not execute 'default.cfg'...");

		DSys::SendConsoleCommand("exec user/default.cfg");
		// load console autoexec config if it exists.
		DSys::SendConsoleCommand("exec user/autoexec.cfg");
		// user.cfg stores current user's configurations
		DSys::SendConsoleCommand("exec user/user.cfg");
		// update the varlist
		DSys::Var::ListUpdateAll();

		// create the window
		DSys::Window::Info		windowInfo = {0};
		windowInfo.title		= DSys::sv_sTitle;
		windowInfo.width		= DSys::sv_iScreenWidth;
		windowInfo.height		= DSys::sv_iScreenHeight;
		windowInfo.colorBits	= DSys::sv_iColorBits;
		windowInfo.depthBits	= DSys::sv_iDepthBits;
		windowInfo.fullscreen	= DSys::sv_bFullscreen;

		DSys::Window::Create( &windowInfo );

		// setup direct input
		DSys::Input::Init( Window::GetHWND(), ::GetModuleHandle(0));
		// init fmod audio system
		DAudio::Init();
		// init the timer
		DSys::Timer::Init();
		// init the console graphics
		Console::GFX_Init();
		// view the intro screen
		DSys::IntroScene();
	}

	bool SystemThink()
	{
		// if the window is not active, then block..
		if (! DSys::Window::Active())
			WaitMessage();

		// finish the message queue
		MSG msg;
		while( PeekMessage(&msg,DSys::Window::GetHWND(),0,0,PM_REMOVE))
		{
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);	// Translate The Message
				DispatchMessage(&msg);	// Dispatch The Message
			}
			else
				return false;
		}		

		// do we have a fixed mouse?
		if( sv_bFixMousePosition )
			SetCursorPos(320,240);

		// update the audio system
		DAudio::Update();

		// update the opengl viewport
		UpdateViewport();

		// update and render the console
		static float tprev = Timer::Time();
		float dt = Timer::Time() - tprev;
		tprev = dt;
		Console::GFX_Render(dt);

		// swap the opengl buffers
		Window::SwapGLBuffers();
		return true;
	}

	void SystemShutdown()
	{
		Input::Shutdown();
		DAudio::Shutdown();
		Timer::Shutdown();
		Console::GFX_Destroy();
		DSys::DestroyConsole();
	}

	void UpdateViewport(){
		if (sv_iScreenHeight ==0) //(division fix)
		{// out of range
			DSys::EchoToConsoleWarning("screen height is out of range...");
			sv_iScreenHeight.setval("1");
			sv_iScreenHeight.update();
		}

		glViewport(0, 0, sv_iScreenWidth, sv_iScreenHeight);		

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Calculate The Aspect Ratio Of The Window
		gluPerspective( gl_fov, sv_iScreenWidth/sv_iScreenHeight, gl_near, gl_far);
		glMatrixMode(GL_MODELVIEW);		// Select The Modelview Matrix
		glLoadIdentity();				// Reset The Modelview Matrix
	}

	/* ------------------------- */
	/*        system tools       */
	/* ------------------------- */


	void Message( const char *fmt, ...)
	{
		va_list ap;
		char text[1024];

		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		MessageBox(NULL, text, "DaherEngine", MB_OK|MB_ICONINFORMATION);
	}

	/*
	---------------
	System Time
	---------------
	*/

	char *StringDate()
	{
		static char buffer[1024];
		SYSTEMTIME systime;
		GetSystemTime(&systime);
		sprintf(buffer, "%d:%d:%d",
			systime.wDay,
			systime.wMonth,
			systime.wYear);
		return buffer;
	}

	char *StringTime()
	{
		static char buffer[1024];
		SYSTEMTIME systime;
		GetSystemTime(&systime);
		sprintf(buffer, "%d:%d:%d",
			systime.wHour,
			systime.wMinute,
			systime.wSecond);
		return buffer;
	}
}// namespace DSys