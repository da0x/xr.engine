/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_FadeScreen.h,v 1.4 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DGL_FADESCREEN_H
#define ___DGL_FADESCREEN_H

namespace DGL {

	//////////////////////////
	// FadeScreen
	class FadeScreen {
		public:
			FadeScreen():	sc(Color::ColorBlack()),
							ec(Color::ColorBlack()),
							tt(0),
							t(0)
			{
			}

			void Init(Color sc, Color ec, float tt)
			{
				this->sc = sc;
				this->ec = ec;
				this->tt = tt;
				this->t  = 0;
			}

			void Update(float msec)
			{
				t += msec;
			}

			bool Render()
			{
				Draw2DRect(0,0,640,480,this->CurrentColor());
				if(!tt || t>tt)
					return false;
				return true;
			}

			void Destroy()
			{
				tt = 0;
			}

			void Restart()
			{
				t = 0;
			}

			Color CurrentColor()
			{
				float ratio = (t/tt);
				Clamp<float>(0,1,ratio);
				
				// combine the two colors
				return sc.CombineWith(ec ,ratio);
			}

		protected:
			Color		sc;		// start color
			Color		ec;		// end color
			float		tt;		// total time
			float		t;		// current time

	};
}

#endif // ___DGL_FADESCREEN_H