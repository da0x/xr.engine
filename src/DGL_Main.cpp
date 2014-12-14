/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_Main.cpp,v 1.3 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#include "DGL_Main.h"
#include "DGL_Ball.h"
#include "DSys_Main.h"
#include "DSys_Var.h"
#include "DSys_Logger.h"



/*
----------------
 dglGetFPS
----------------
*/

namespace DGL {

	 int GetFPS(float msec){
		static	const int	fpsFrames	= 4;	// flickering fix
		static	float		time;
		static	float		oldtime;
		static	float		fpsTime[fpsFrames];
				float		total;
		static	int			fps;
		static	int			index;
				int			i;

		time+= msec;
		fpsTime[ index ]= time - oldtime;
		oldtime= time;

		if( index >= fpsFrames ){
			index = total= 0;
			for(i=0; i< fpsFrames; i++)
				total+= fpsTime[i];
			if(!total)
				total= 1;
			fps= fpsFrames / total*1000;
		} else
			index ++;
		return fps;
	}

	
	namespace MatrixOp {
		/* ===================== */
		/*    Ortho    */
		/* ===================== */

		float Ortho::orthoMatrix[16]={
			0.003125f,	0.000000f,	0.000000f,	0.000000f,
			0.000000f,	0.004167f,	0.000000f,	0.000000f,
			0.000000f,	0.000000f,	-1.000000f,	0.000000f,
			-1.000000f,	-1.000000f,	0.000000f,	1.000000f
		};

		void Ortho::Begin(){
			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadMatrixf(orthoMatrix);

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
            
			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void Ortho::End(){
			glMatrixMode( GL_PROJECTION );	glPopMatrix();
			glMatrixMode( GL_MODELVIEW );	glPopMatrix();
//			glEnable( GL_DEPTH_TEST );
//			glDisable( GL_BLEND );
			glPopAttrib();
		}

		/* ===================== */
		/*    BalloonPoint       */
		/* ===================== */
		void BalloonPoint::Begin(Vector v){
			float matrix[16];
			glPushMatrix();
			glTranslatef(v.x_(),v.y_(),v.z_());
			glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
			#define _M(row,col)  matrix[col*4+row]
				_M(0, 0) = 1.0f;
				_M(0, 1) = 0.0f;
				_M(0, 2) = 0.0f;
				_M(1, 0) = 0.0f;
				_M(1, 1) = 1.0f;
				_M(1, 2) = 0.0f;
				_M(2, 0) = 0.0f;
				_M(2, 1) = 0.0f;
				_M(2, 2) = 1.0f;
				_M(3, 0) = v.x_();
				_M(3, 1) = v.y_();
				_M(3, 2) = v.z_();
			#undef _M			
			glLoadMatrixf(matrix);
		}
		void BalloonPoint::End(){
			glPopMatrix();
		}
	}



	void LogPrint(const char *fmt,...){
		va_list ap;
		char text[1024];
		va_start(ap,fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		DSys::Logger::Print(text);
	}

	void LogError(const char *fmt,...){
		va_list ap;
		char text[1024];
		va_start(ap,fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		DSys::Logger::Error(text);
	}


#pragma message("Wipe this shit out of here")

	//
	// DFX.H
	//

	// Quadratics
	GLUquadricObj *quadricObj;		// Quadric Object
	void InitQuadrics(){
		quadricObj = gluNewQuadric();
		gluQuadricNormals(quadricObj, GLU_SMOOTH);
		gluQuadricTexture(quadricObj, GL_TRUE);
	}


	//
	// Ball.h
	//
	DGL::Ball	*Ball::list = NULL;


}// namespace DGL;