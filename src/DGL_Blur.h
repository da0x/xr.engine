/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_Blur.h,v 1.3 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DBLUR_H
#define ___DBLUR_H

/*
	TODO List:
		- ... -
*/


namespace DGL {

	class Blur{
		protected:
			GLuint		blurTexture;						// An Unsigned Int To Store The Texture Number

		private:
/*			GLuint emptyTexture()							// Create An Empty Texture
			{
				GLuint txtnumber;						// Texture ID
				unsigned int* data;						// Stored Data

				// Create Storage Space For Texture Data (128x128x4)
				data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];

				ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int)));

				glGenTextures(1, &txtnumber);
				glBindTexture(GL_TEXTURE_2D, txtnumber);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
								GL_RGBA, GL_UNSIGNED_BYTE, data);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

				delete [] data;

				return txtnumber;
			}
*/		public:
			void ViewOrtho(){
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();
				glLoadIdentity();
				glOrtho( 0, 640 , 480 , 0, -1, 1 );
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glLoadIdentity();
			}

			void ViewPerspective(){
				glMatrixMode( GL_PROJECTION );
				glPopMatrix();
				glMatrixMode( GL_MODELVIEW );
				glPopMatrix();
			}

			void BeginBlur(){
				glPushAttrib(GL_VIEWPORT_BIT);
				glViewport(0,0,256,256);
			}
			void EndBlur(){
				glBindTexture(GL_TEXTURE_2D,blurTexture);
				glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 256, 256, 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glPopAttrib();
			}
			void DrawBlur(int times, float inc){
				float spost = 0.0f;
				float alphainc = 0.9f / times;
				float alpha = 0.2f;


				glPushAttrib(GL_ENABLE_BIT|GL_TEXTURE_BIT);
				glDisable(GL_DEPTH_TEST);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				glEnable(GL_BLEND);
				glBindTexture(GL_TEXTURE_2D,blurTexture);
				ViewOrtho();

				alphainc = alpha / times;

				glBegin(GL_QUADS);
				for (int num = 0;num < times;num++){
					glColor4f(1.0f, 1.0f, 1.0f, alpha);
					glTexCoord2f(0+spost,1-spost);
					glVertex2f(0,0);

					glTexCoord2f(0+spost,0+spost);
					glVertex2f(0,480);

					glTexCoord2f(1-spost,0+spost);
					glVertex2f(640,480);

					glTexCoord2f(1-spost,1-spost);
					glVertex2f(640,0);

					spost += inc;
					alpha = alpha - alphainc;
				}
				glEnd();
				ViewPerspective();
				glPopAttrib();
			}
			__forceinline GLuint Texture(){ return blurTexture; }
	};
}//namespace DGL

#endif // ___DBLUR_H