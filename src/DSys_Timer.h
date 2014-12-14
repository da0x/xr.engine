/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Timer.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DSYS_TIMER_H
#define ___DSYS_TIMER_H

namespace DSys {

	class Timer{
		private:
			static bool			valid;						// true if the timer is valid
			static __int64		frequency;					// Timer Frequency
			static float		resolution;					// Timer Resolution
			static DWORD		mmTimerStart;				// Multimedia Timer Start Value
			static DWORD		mmTimerElapsed;				// Multimedia Timer Elapsed Time
			static DWORD		mmTimerPause;				// Stores the pause time
			static bool			performanceTimer;			// Using The Performance Timer?
			static __int64		performanceTimerStart;		// Performance Timer Start Value
			static __int64		performanceTimerElapsed;	// Performance Timer Elapsed Time
			static __int64		performanceTimerPause;		// Stores the pause time

			static void			performanceTimerInit();
			static void			mmTimerInit();

			static float		performanceTimerGetTime();
			static float		mmTimerGetTime();
		public:
			static void			Init();						// Initializes the timer
			static float		Time();						// Gets Time In Milliseconds
			static void			Shutdown();				// Terminates the timer
			static void			Pause();					// Sets a pause point
			static void			Unpause();					// Resumes from the paused point
	};
}

#endif // ___DSYS_TIMER_H