/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DMath_Random.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


namespace DMath 
{
	/*-----------------
		Random
	-----------------*/
	
	class Random {
		
		public:
			static inline void	Randomize();
			static inline void	Seed ( unsigned int );
			static inline int	Int ( void );
			static inline float Float ();

		private:
			static long holdrand;
	};

} // namespace DMath