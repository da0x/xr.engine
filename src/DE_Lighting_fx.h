/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.8 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DE_Lighting_fx.h,v 1.8 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___DLIGHING_FX_H
#define ___DLIGHING_FX_H

namespace DGL {

	class Package
		{
		private: Texture texLeft;
				 Texture texRight;
				 Texture texFront;
				 Texture texBack;
				 Texture texUp;
				 Texture texDown;
				 Texture ref;

				 static const float scale;// = 1.0f;
				 static const float width;// = scale * 10;
				 static const float height;// = scale * 14;
				 static const float length;// = scale * 2;
		public: void Init()
					{
					this->texFront.Build( "textures/pk_front.tga" );
					this->texBack.Build( "textures/pk_back.tga" );
					this->texUp.Build( "textures/pk_up.tga" );
					this->texDown.Build( "textures/pk_down.tga" );
					this->texLeft.Build( "textures/pk_left.tga" );
					this->texRight.Build( "textures/pk_right.tga" );
					this->ref.Build( "textures/refmap.tga");
					}

				void Render() const 
					{
					//
					// Pass #1
					//

					//front
					glBindTexture(GL_TEXTURE_2D, this->texFront);
					glBegin(GL_QUADS);
					glNormal3fv( Vector::znorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( -width , -height, length);
					glNormal3fv( Vector::znorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( width , -height, length);
					glNormal3fv( Vector::znorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( width , height, length);
					glNormal3fv( Vector::znorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( -width , height, length);
					glEnd();

					// back
					glBindTexture(GL_TEXTURE_2D, this->texBack);
					glBegin(GL_QUADS);
					glNormal3fv( -Vector::znorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( width , -height, -length);
					glNormal3fv( -Vector::znorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( -width , -height, -length);
					glNormal3fv( -Vector::znorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( -width , height, -length);
					glNormal3fv( -Vector::znorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( width , height, -length);
					glEnd();

					// left
					glBindTexture(GL_TEXTURE_2D, this->texLeft);
					glBegin(GL_QUADS);
					glNormal3fv( -Vector::xnorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( -width , -height, -length);
					glNormal3fv( -Vector::xnorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( -width , -height, length);
					glNormal3fv( -Vector::xnorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( -width , height, length);
					glNormal3fv( -Vector::xnorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( -width , height, -length);
					glEnd();
					
					// right
					glBindTexture(GL_TEXTURE_2D, this->texRight);
					glBegin(GL_QUADS);
					glNormal3fv( Vector::xnorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( width , -height, length);
					glNormal3fv( Vector::xnorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( width , -height, -length);
					glNormal3fv( Vector::xnorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( width , height, -length);
					glNormal3fv( Vector::xnorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( width , height, length);
					glEnd();

					// up
					glBindTexture(GL_TEXTURE_2D, this->texUp);
					glBegin(GL_QUADS);
					glNormal3fv( Vector::ynorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( -width , height, length);
					glNormal3fv( Vector::ynorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( width , height, length);
					glNormal3fv( Vector::ynorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( width , height, -length);
					glNormal3fv( Vector::ynorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( -width , height, -length);
					glEnd();

					// down
					glBindTexture(GL_TEXTURE_2D, this->texDown);
					glBegin(GL_QUADS);
					glNormal3fv( -Vector::ynorm() );
					glTexCoord2f( 0, 0);
					glVertex3f( -width , -height, -length);
					glNormal3fv( -Vector::ynorm() );
					glTexCoord2f( 1, 0);
					glVertex3f( width , -height, -length);
					glNormal3fv( -Vector::ynorm() );
					glTexCoord2f( 1, 1);
					glVertex3f( width , -height, length);
					glNormal3fv( -Vector::ynorm() );
					glTexCoord2f( 0, 1);
					glVertex3f( -width , -height, length);
					glEnd();
					}

					void Destroy()
						{
						this->texBack.Delete();
						this->texUp.Delete();
						this->texFront.Delete();
						this->texDown.Delete();
						this->texLeft.Delete();
						this->texRight.Delete();
						}
		};
		const float Package::scale = 1.0f;
		const float Package::width = scale * 10;
		const float Package::height = scale * 14;
		const float Package::length = scale * 2;

	class Room {
		private:
			Texture	texture;
			Texture cromEnv;
			GLuint	list;

		public:
			const static int ROOM_LEN = 20;
			const static int ROOM_HIT = 10;
			const static int ROOM_STP = 1;
			const static int ROOM_TEX_REPEAT = 4;

			void Init(){
				texture.Build("textures/metalicfloor.jpg");
				cromEnv.Build("textures/ref.tga");

				list = glGenLists(1);
				glNewList(list, GL_COMPILE);
					glColor4fv(Color::ColorWhite());
					glMaterialfv(GL_FRONT, GL_AMBIENT, Color(0.6f, 0.6f, 0.6f, 1.0f ));
					glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(0.8f, 0.9f, 0.9f, 1.0f ));
					glMaterialfv(GL_FRONT, GL_SPECULAR, Color(0.6f, 0.6f, 0.6f, 1.0f ));
					glMaterialf(GL_FRONT, GL_SHININESS, 10.0f );

					{ // upper and lower surfaces
						glPushMatrix();
						glTranslatef(-ROOM_LEN/2.0f, 0.0f, -ROOM_LEN/2.0f);
						for(int k =0; k< ROOM_LEN; k+=ROOM_STP){
							for(int i =0; i< ROOM_LEN; i+=ROOM_STP){
								glBegin(GL_QUADS); // lower
									glNormal3f(0.0f, 1.0f, 0.0f);
									glTexCoord2f(i*ROOM_TEX_REPEAT/(float)ROOM_LEN , k*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i, -ROOM_HIT/2.0f, k);
									glTexCoord2f(i*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i, -ROOM_HIT/2.0f, k+ROOM_STP);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i+ROOM_STP, -ROOM_HIT/2.0f, k+ ROOM_STP);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i+ROOM_STP, -ROOM_HIT/2.0f, k);
								glEnd();
								glBegin(GL_QUADS); // upper
									glNormal3f(0.0f,-1.0f, 0.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i, ROOM_HIT/2.0f, k);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i+ROOM_STP, ROOM_HIT/2.0f, k);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i+ROOM_STP, ROOM_HIT/2.0f, k+ ROOM_STP);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (k+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN);
									glVertex3f( i, ROOM_HIT/2.0f, k+ROOM_STP);
								glEnd();
							}
						}
						glPopMatrix();
					}
					{ // fornt and back surfaces
						glPushMatrix();
						glTranslatef(-ROOM_LEN/2.0f, -ROOM_HIT/2.0f, 0.0f);
						for (int j=0; j< ROOM_HIT; j+= ROOM_STP){
							for (int i=0; i< ROOM_LEN; i+=ROOM_STP){
								glBegin(GL_QUADS); // front
									glNormal3f(0.0f, 0.0f, 1.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j, -ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);;
									glVertex3f( i+ROOM_STP, j, -ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j+ROOM_STP, -ROOM_LEN/2.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j+ROOM_STP, -ROOM_LEN/2.0f);
								glEnd();
								glBegin(GL_QUADS); // back
									glNormal3f(0.0f, 0.0f, -1.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j, ROOM_LEN/2.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j+ROOM_STP, ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j+ROOM_STP, ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j, ROOM_LEN/2.0f);
								glEnd();
							}
						}
						glPopMatrix();
					}
					{ // left and right surfaces
						glPushMatrix();
						glRotatef(90, 0.0f, 1.0f, 0.0f);
						glTranslatef(-ROOM_LEN/2.0f, -ROOM_HIT/2.0f, 0.0f);
						for (int j=0; j< ROOM_HIT; j+= ROOM_STP){
							for (int i=0; i< ROOM_LEN; i+=ROOM_STP){
								glBegin(GL_QUADS); // left
									glNormal3f(0.0f, 0.0f, 1.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j, -ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);;
									glVertex3f( i+ROOM_STP, j, -ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j+ROOM_STP, -ROOM_LEN/2.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j+ROOM_STP, -ROOM_LEN/2.0f);
								glEnd();
								glBegin(GL_QUADS); // right
									glNormal3f(0.0f, 0.0f, -1.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j, ROOM_LEN/2.0f);
									glTexCoord2f((i)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i, j+ROOM_STP, ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j+ROOM_STP, ROOM_LEN/2.0f);
									glTexCoord2f((i+ROOM_STP)*ROOM_TEX_REPEAT/(float)ROOM_LEN , (j)*ROOM_TEX_REPEAT/(float)ROOM_HIT);
									glVertex3f( i+ROOM_STP, j, ROOM_LEN/2.0f);
								glEnd();
							}
						}
						glPopMatrix();
					}
				glEndList();
			}

			void Render(){
				glBindTexture(GL_TEXTURE_2D, texture);
                glCallList(list);
/*
				glBindTexture(GL_TEXTURE_2D, this->cromEnv);
				glPushAttrib( GL_ENABLE_BIT);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
				glEnable(GL_BLEND);
				glBlendFunc( GL_DST_COLOR, GL_ONE);
				glCallList(list);
				glPopAttrib();*/
			}

			void Destroy(){
				texture.Delete();
				cromEnv.Delete();
				glDeleteLists(list, 1);
			}

	};

	class Lighting_fx :
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

			Room				room;
			ModelMilkshape		quad;
			Package				package;
			Camera				camera;
			FireEngine			fireEngineLeft, fireEngineRight;
			FadeScreen			fadein;
		public:
			void Init(){
				room.Init();
				m_fSeconds = 0;
				// setup light0
				m_fIsDirectional = 1.0f;
				glLightfv(GL_LIGHT0, GL_AMBIENT, Color(0.5f, 0.3f, 0.1f, 1.0f));
				glLightfv(GL_LIGHT0, GL_DIFFUSE, Color(0.8f, 0.7f, 0.5f, 1.0f));
				glLightfv(GL_LIGHT0, GL_SPECULAR, Color(1.0f, 1.0f, 1.0f, 1.0f));
				glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
				glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2f);
				glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005f);
				glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Color(0.0f,0.0f,0.0f,1.0f));
				glEnable(GL_LIGHT0);

				this->fireEngineLeft.Init(
					Vector(-2.5,-4,0),
					Vector(0,5,0),
					Vector(0,0,0),
					DGL::Color(1.0f,1.0f,1.0f,1.0f),
					DGL::Color::ColorRed(),
					0.25f,
					2,
					0);

				this->fireEngineRight.Init(
					Vector(2.5,-4,0),
					Vector(0,5,0),
					Vector(0,0,0),
					DGL::Color(1.0f,1.0f,1.0f,1.0f),
					DGL::Color::ColorRed(),
					0.25f,
					2,
					0);

				this->quad.LoadModelData( "models/quad.ms3d");
				this->package.Init();
				this->fadein.Init(Color(0.0f,0.0f,0.0f,1.0f),Color(0.0f,0.0f,0.0f,0.0f), 3000);
			}

			void Update(float msec){
				this->fireEngineLeft.Update(msec);
				this->fireEngineRight.Update(msec);

				m_fSeconds += msec / 1000.0f;
				Vector enginePos(
							(float)sin(m_fSeconds)*room.ROOM_LEN*0.25f,
							(float)sin(m_fSeconds*0.26f)*room.ROOM_HIT*0.25f-2.0f,
							(float)cos(m_fSeconds*0.6f)*room.ROOM_LEN*0.25f);
//				m_vLightPosition.Set(enginePos);
//				this->fireEngine.UpdatePosition(enginePos);
				this->quad.Update(msec);
				this->fadein.Update(msec);

				// get current frustum for model clipping
				DGL::Model::_FrustumUpdate();
			}

			void Render(){
				glClearColor(0,.08f,0.2f,1);
				glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

				// setup the lights
				glLightfv(GL_LIGHT0, GL_POSITION, m_fvLightPosition);

				// render the scene
				room.Render();

				

				// render the inner model
				glPushMatrix();
				glScalef(0.1f,0.1f,0.1f);
//				glTranslatef(0, 1, -25);

				glRotatef(m_fSeconds*100, 0, 1, 0);

				this->quad.Render();
//				this->package.Render();
				glPopMatrix();
				
				// fire :)
				this->fireEngineLeft.Render();
				this->fireEngineRight.Render();
//				this->fadein.Render();

/**/
				glDisable(GL_TEXTURE_2D);
					// render the light
					glPushMatrix();
						glTranslatef(m_vLightPosition.x_(), m_vLightPosition.y_(), m_vLightPosition.z_());
						static bool lighting = glIsEnabled(GL_LIGHTING);
						glMaterialf(GL_FRONT, GL_SHININESS, 100.0f );
						if( lighting) glDisable(GL_LIGHTING);
						Color::ColorCyan().MakeCurrentRGB();
						DrawSphere(0.2);
						Color::ColorWhite().MakeCurrentRGB();
						if( lighting) glEnable(GL_LIGHTING);
						glMaterialf(GL_FRONT, GL_SHININESS, 0.0f );
					glPopMatrix();

#if 0
					// render the 3 rings
					glMaterialf(GL_FRONT, GL_SHININESS, 100);
					glPushMatrix();
						glMaterialfv(GL_FRONT, GL_AMBIENT, Color(0.9f, 0.6f, 0.6f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(0.8f, 0.5f, 0.5f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_SPECULAR, Color(1.0f, 1.0f, 1.0f, 1.0f ));

						glRotatef(m_fSeconds*100, 1, 0, 0);
						DrawTorus(0.1f, 1);
					glPopMatrix();

					glPushMatrix();
						glMaterialfv(GL_FRONT, GL_AMBIENT, Color(0.9f, 0.9f, 0.6f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(0.8f, 0.8f, 0.5f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_SPECULAR, Color(1.0f, 1.0f, 1.0f, 1.0f ));

						glRotatef(m_fSeconds*50, 0, 1, 0);
						DrawTorus(0.1f, 1.5f);
					glPopMatrix();

					glPushMatrix();
						glMaterialfv(GL_FRONT, GL_AMBIENT, Color(0.2f, 0.5f, 0.9f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(0.2f, 0.6f, 0.9f, 1.0f ));
						glMaterialfv(GL_FRONT, GL_SPECULAR, Color(1.0f, 1.0f, 1.0f, 1.0f ));

						glRotatef(m_fSeconds*25, 1, 0, 1);
						DrawTorus(0.1f, 2);
					glPopMatrix();
#endif
				glEnable(GL_TEXTURE_2D);
/**/

			}

			void Destroy(){
				room.Destroy();
				quad.Destroy();
				this->fireEngineLeft.Destroy();
				this->fireEngineRight.Destroy();
				this->package.Destroy();
				this->fadein.Destroy();
			}

			void Restart()
				{
				this->fadein.Restart();
				}
	};
} // namespace DGL




#endif // ___DLIGHING_FX_H