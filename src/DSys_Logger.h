/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Logger.h,v 1.4 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DSYS_LOGGER_H
#define ___DSYS_LOGGER_H

namespace DSys {
	//------------- Logging class -------------//

	
	class Logger {
		private:
			static Daher::Logger	dlog;
			static int				level;
			static Var_bool         show_debug_info;
		public:
			static void Print(const char *fmt, ...);
			static void Error(const char *fmt, ...);
			static void Warning(const char *fmt, ...);
			static void Good(const char *fmt, ...);
			static bool UseExtension( const char *name, bool available, Var& cvar);

			static void DSys::Logger::EnterLevel();
			static void DSys::Logger::LeaveLevel();
			
			class Level {
			public:
				Level();
				~Level();
			};

#			define Logger_EnterLevel() DSys::Logger::Level logger_level_instance
	};
}

#endif // ___DSYS_LOGGER_H