/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_Fog.h,v 1.3 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DFOG_H
#define ___DFOG_H

/*
TODO List:
- ...
*/


namespace DGL {
	class Fog{
		private:
			float		FogDensity;					// density
			bool		bFog;						// for status
			float		fogColor[4];				// fog color
			float		fogStart;					// fog start
			float		fogEnd;						// fot end
		public:
			Fog	(){
				FogDensity = 0.2f;
				bFog = true;
				fogColor[0]=fogColor[1]=fogColor[2]=fogColor[3]= 1.0f;
				fogStart = 0.0f;
				fogEnd = 20.0f;
			}
			void SetDensity(float d){
				if(FogDensity > 1) FogDensity = 1;
				if(FogDensity < 0) FogDensity = 0;
				glFogf(GL_FOG_DENSITY, FogDensity);
			}
			void SetStartEnd(float start, float end){
				fogStart = start;
				fogEnd = end;
			}
			void Toogle(){
				bFog = !bFog;
				if(bFog)
					glEnable(GL_FOG);
				else
					glDisable(GL_FOG);
			}
			void SetColor(float r, float g, float b, float a){
				fogColor[0]= r;
				fogColor[1]= g;
				fogColor[2]= b;
				fogColor[3]= a;
			}
			void Init(){
				// set the fog mode
				glFogi(GL_FOG_MODE, GL_LINEAR);
				// set the fog color and clear color
				glFogfv(GL_FOG_COLOR, fogColor);
				glClearColor(fogColor[0],fogColor[1],fogColor[2],fogColor[3]);
				// set the density
				glFogf(GL_FOG_DENSITY, FogDensity);
				// how acurate the calculated fog is
				glHint(GL_FOG_HINT, GL_NICEST);
				// set start and end
				glFogf(GL_FOG_START, fogStart);
				glFogf(GL_FOG_END, fogEnd);
			}
			void Apply(){
				glEnable(GL_FOG);
			}
			void Disable(){
				glDisable(GL_FOG);
			}
	};

}//namespace DGL
#endif // ___DFOG_H