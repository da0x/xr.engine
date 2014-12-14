/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:22:03 $
	$Id: Main.cpp,v 1.4 2004/07/31 19:22:03 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



/*
TODO List:
- ...
*/


#include "DSys.h"


/*-------------------------------------------*/
/*			       Libraries                 */
/*-------------------------------------------*/


#pragma comment( lib, "User32.lib")
#pragma comment( lib, "OpenGL32.lib" )
#pragma comment( lib, "GLu32.lib" )
#pragma comment( lib, "WinMM.lib" )
#pragma comment( lib, "AdvAPI32.lib")
#pragma comment( lib, "GDI32.lib")
#pragma comment( lib, "DXguid.lib")
#pragma comment( lib, "OLE32.lib")

// try catch macros
#ifdef _DEBUG
# define Macro_Try()
# define Macro_CatchLoop()
# define Macro_CatchAll()
#else
# define Macro_Try()	try {
# define Macro_CatchLoop()	\
			} catch (Daher::Exception ex) {\
				DSys::Message("An Unhandled Exception in main loop.\n"\
					"- Exception Message:\n %s", ex.What());\
				/*Daher::CallStackTrace::Dump();*/\
			} catch (...) {\
				DSys::Message("An Unhandled Exception in main loop.");\
				/*Daher::CallStackTrace::Dump();*/\
			}
# define Macro_CatchAll() \
			} catch (Daher::Exception ex) {\
				DSys::Message("An Exception Occured in main thread.\n"\
					"- Exception Message:\n %s", ex.What());\
				/*Daher::CallStackTrace::Dump();*/\
			} catch (...) {\
				DSys::Message("An Unhandled Exception Occured main thread.");\
				/*Daher::CallStackTrace::Dump();*/\
			}
#endif


// farward declerations for the scene
bool Init();
void AddConsoleCommands();
void Update(float msec);
void Render3D();
void Render2D(float msec);
void Shutdown();

/*---------------------
    Main Window Entry
  ---------------------*/

int WINAPI WinMain(HINSTANCE	hInstance,
				   HINSTANCE	hPrevInstance,
				   LPSTR		commandArg,
				   int			nCmdShow)
{
std::string Args = commandArg;
/*/
int main(int argi, char **commandArg)
{
std::string Args = *commandArg;
/*/
	DSys::Logger::Print("WinMain Starts");
	Macro_Try();
		

		DSys::SystemInitialize( Args );
		int CmdShow = DSys::ConfigDialog::Show();
		if( !CmdShow )
		{// aborted
			return -1;
		}

		DSys::SystemStart();

		if(::Init())
		{
			::AddConsoleCommands();

			Macro_Try();

				/*-----------
				  Main Loop
				-----------*/
				DSys::Timer::Init();
				float	timeprev = DSys::Timer::Time();
				float	time, dt;
				while( DSys::SystemThink() )
				{					
					time = DSys::Timer::Time();
					dt = time - timeprev;
					timeprev = time;

					::Update(dt);
					::Render3D();		// Draw The 3D Scene
					::Render2D(dt);		// Draw The 2D Scene
				}

			Macro_CatchLoop();

			::Shutdown();
		}// ::Init
		
		DSys::SystemShutdown();

	Macro_CatchAll();
	return 0;
}
