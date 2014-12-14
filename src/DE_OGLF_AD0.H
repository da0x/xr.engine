/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DE_OGLF_AD0.H,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___OGLF_AD0
#define ___OGLF_AD0

namespace OGLF {

	class AD0 :
		public Demo::Scene {
		private:

			union {	
				struct {
					
						Vector	m_vLightPosition;
					GLfloat		m_fIsDirectional;
				};
				GLfloat			m_fvLightPosition[4];
			};
			GLfloat				m_fLightIntensity;
			float				m_fSeconds;

			// for the logo
			DGL::Texture		refMap;
			DGL::Font3D			font3d;
			HDC					hDC;
		public:
			AD0(HDC DC): hDC(DC)
			{
			}

			void Init(){
				m_fSeconds = 0;
				// setup light0
				m_fIsDirectional = 1.0f;
				glLightfv(GL_LIGHT0, GL_AMBIENT, DGL::Color(0.5f, 0.5f, 0.5f, 1.0f));
				glLightfv(GL_LIGHT0, GL_DIFFUSE, DGL::Color(0.6f, 0.8f, 0.8f, 1.0f));
				glLightfv(GL_LIGHT0, GL_SPECULAR, DGL::Color(1.0f, 1.0f, 1.0f, 1.0f));
				glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
				glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2f);
				glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005f);
				glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, DGL::Color(0.0f,0.0f,0.0f,1.0f));
				glEnable(GL_LIGHT0);

				this->refMap.Build("textures/refmap.tga");
				font3d.Build("Arial", this->hDC);
			}

			void Update(float msec){

				m_fSeconds += msec / 1000.0f;
				m_vLightPosition.Set(
							(float)sin(m_fSeconds)*3,
							(float)sin(m_fSeconds*0.26f)*3,
							(float)cos(m_fSeconds*0.6f)*3);
			}

			void Render(){
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
				// setup the lights
				glLightfv(GL_LIGHT0, GL_POSITION, m_fvLightPosition);


				glEnable(GL_LIGHTING);

					// render the logo
					glMaterialf(GL_FRONT, GL_SHININESS, 100);
					glPushMatrix();
						glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, DGL::Color::ColorGold());
						glMaterialfv(GL_FRONT, GL_SPECULAR, DGL::Color(1.0f, 1.0f, 1.0f, 1.0f ));

//						glRotatef(m_fSeconds*100, 0, 1, 0);

						glBindTexture(GL_TEXTURE_2D, this->refMap);
						glPushAttrib(GL_ENABLE_BIT);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);
						glScalef(1,1.5f,3);
						this->font3d.Print("OpenGL Forums");
						glPopAttrib();
					glPopMatrix();
			}

			bool Done()
			{
				return false;
			}

			void Restart()
			{
			}

			void Destroy()
			{
				this->refMap.Delete();
			}
	};
} // namespace DGL




#endif // ___DLIGHING_FX_H