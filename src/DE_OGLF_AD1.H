/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DE_OGLF_AD1.H,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___OGLF_AD1
#define ___OGLF_AD

namespace OGLF {

	class AD1 :
		public Demo::Scene {

	private:
			DGL::TextImage		*textImage;

	public:
			void Init()
			{
				this->textImage = new DGL::TextImage("textures/logoOGLF.jpg",
														"OpenGLForums",
														20,
														false);
			}

			void Update(float msec)
			{
			}

			void Render()
			{
				glClearColor(0,0,0,1);
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				
				this->textImage->Render();
			}

			void Destroy()
			{
				delete this->textImage;
			}

			bool Done()
			{
				return false;
			}

			void Restart()
			{
			}

	};
}

#endif // ___OGLF_AD1