/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Main.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DGLU_H
#define ___DGLU_H


// OS and OpenGL
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
//#include "gl/glaux.h"
#include "DShared.h"



/*
===========================
Utilities for DGL namespace
===========================
*/

namespace DGL {
	int GetFPS(float msec);
	void LogPrint(const char *, ...);		// logging
	void LogError(const char *, ...);




	namespace MatrixOp {
		
		/*
		==========================
		Ortho
		==========================
		*/
		class Ortho {
			public:
				enum {
					MAX_X = 640,
					MAX_Y = 480
				};
			private:
				static float	orthoMatrix[16];
			public:
				static void Begin();
				static void End();
		};
		/*
		==========================
		BalloonPoint
		==========================
		*/
		class BalloonPoint {
			public:
				static void Begin(Vector position);
				static void End();
		};

	}
}


#endif // ___DGLU_H