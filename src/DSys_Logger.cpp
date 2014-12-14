/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.5 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Logger.cpp,v 1.5 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


/*
TODO List:
- ...
*/

#include "DSys.H"

using namespace DSys;

/*
===========================================

  Logger::Error/Logger::Warning/Logger::Print

===========================================
*/

Daher::Logger		Logger::dlog("user/console.log", false);
int					Logger::level = 0;
Var_bool			Logger::show_debug_info("show_debug_info", "1");
	
void Logger::Print(const char *fmt, ...){
		va_list		argptr;
		DSTR		text;

		va_start (argptr, fmt);
		vsprintf (text, fmt, argptr);
		va_end (argptr);
		EchoToConsole(text);
		dlog.Printf("[%s]\t- ", StringTime());
		for(int i=0; i< level; i++)
			dlog.Printf("%c", '\t');
		dlog.Printf("%s\n", text);

		if( show_debug_info )
			{
			std::cout << text << std::endl;
			std::cout.flush();
			}
	}
	
void Logger::Error(const char *fmt, ...){
		va_list		argptr;
		DSTR		text;

		va_start (argptr, fmt);
		vsprintf (text, fmt, argptr);
		va_end (argptr);

		EchoToConsoleError(text);
		dlog.Printf("[%s]\t! ", StringTime());
		for(int i=0; i< level; i++)
			dlog.Printf("%c", '\t');
		dlog.Printf("%s\n", text);

		if( show_debug_info )
			{
			std::cout << text << std::endl;
			std::cout.flush();
			}
	}

void Logger::Warning(const char *fmt, ...){
		va_list		argptr;
		DSTR		text;

		va_start (argptr, fmt);
		vsprintf (text, fmt, argptr);
		va_end (argptr);
		EchoToConsoleWarning(text);
		dlog.Printf("[%s]\t~ ", StringTime());
		for(int i=0; i< level; i++)
			dlog.Printf("%c", '\t');
		dlog.Printf("%s\n", text);

		if( show_debug_info )
			{
			std::cout << text << std::endl;
			std::cout.flush();
			}
	}

void Logger::Good(const char *fmt, ...){
		va_list		argptr;
		DSTR		text;

		va_start (argptr, fmt);
		vsprintf (text, fmt, argptr);
		va_end (argptr);

		EchoToConsoleGood(text);
		dlog.Printf("[%s]\t+ ", StringTime());
		for(int i=0; i< level; i++)
			dlog.Printf("%c", '\t');
		dlog.Printf("%s\n", text);

		if( show_debug_info )
			{
			std::cout << text << std::endl;
			std::cout.flush();
			}
	}

void Logger::EnterLevel()
	{
		level ++;
	}

void Logger::LeaveLevel()
	{
		if(level >= 0)
			level --;
		else
			level = 0;
	}

Logger::Level::Level()
	{
		Logger::EnterLevel();
	}
Logger::Level::~Level()
	{
		Logger::LeaveLevel();
	}