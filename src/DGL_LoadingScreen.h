/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_LoadingScreen.h,v 1.3 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DLOADINGSCREEN_H
#define ___DLOADINGSCREEN_H

/*
TODO List:
- ...
*/

#include "DGL_Font.h"
#include "DSys_Timer.h"

namespace DGL {

		
	class LoadingScreen {

			float		percent;	// current percent to draw
			Texture		tex;		// texture
			DSTR		text;		// text
			Font		font;		// font
			DSys::Timer timer;		// timer
		public:

			void Init();
			void SetStage(int precent, char *fmt, ...);
			~LoadingScreen();
		private:
			void PopFrame();
	};

}//namespace DGL
#endif // ___DLOADINGSCREEN_H
