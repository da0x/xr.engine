/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Main.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DSYSTEM_H
#define ___DSYSTEM_H

/*
TODO List:
- ...
*/


namespace DSys
{
	static const char *Version = "Daher Engine 2.00 Alpha";

	void SystemInitialize( std::string commandArg);
	void SystemStart();
	bool SystemThink();
	void SystemShutdown();

	void Message( const char *fmt, ...);	// Displays a message to the user.
	void GetSysInfo();						// echos system info into console and sets them into the cvars sys_*

	// console
	void InitConsole(void);
	void DestroyConsole(void);
	void AddConsoleCommand(char *name, void ( *cmdptr)(char *fmt) );
	void AddConsoleCommand(char *name, void ( *cmdptr)(void) );
	void SendConsoleCommand(char *fmt); // Execute a command as if was writen in the console
	void EchoToConsole(char *fmt);
	void EchoToConsoleError(char *fmt);
	void EchoToConsoleWarning(char *fmt);
	void EchoToConsoleGood(char *fmt);

	void IntroScene();
	void UpdateViewport();

	char *StringDate();
	char *StringTime();
}


#endif // ___DSYSTEM_H