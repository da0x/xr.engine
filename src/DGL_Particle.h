/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Particle.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DGL_PARTICLE_H
#define ___DGL_PARTICLE_H

/*
TODO List:
- ...
*/

/* ----------------------- */
/*     Particle Engine     */
/* ----------------------- */

namespace DGL {

	class Particle {
			private:
				bool			valid;
				Vector			position;
				Vector			velocity;
				float			life;
				float			maxLife;

			public:
				Particle():
						valid(0),
						life(0),
						position(0,0,0),
						velocity(0,0,0)
				{ }
				inline void Init(Vector position, Vector velocity){
					this->position = position;
					this->velocity = velocity;
				}
				inline void Start(float maxLife){
					valid		= true;
					life		= 0;
					this->maxLife = maxLife;
				}
				inline void Update(Vector gravity, float seconds){
					if(valid){
						life +=seconds;
						if(life>=maxLife){
							End();
							return;
						}
						velocity += gravity*seconds;
						position += velocity*seconds;
					}
				}
				inline void End(){
					this->valid = false;
				}
				inline bool Valid(){
					return this->valid;
				}
				inline Vector Position(){
					return Vector(this->position);
				}
				inline float Life(){
					return float(this->life);
				}
				inline float MaxLife(){
					return float(this->maxLife);
				}
		};

	class ParticleEngine {

		protected:
			int				maxParticles;
			int				maxParticleLife;
			Particle		*particles;
			Vector	position;
			Vector	gravity;
			Vector	force;
			float			radius;
			Color			endColor;
			Color			startColor;
			float			randomFactor;
			Texture			texture;
		private:
			float			lifeRatio;
			Color			finalColor;

		public:
			ParticleEngine():
					maxParticles(0),
					maxParticleLife(0),
					particles(NULL),
					gravity(0,0,0),
					position(0,0,0),
					force(0,0,0),
					radius(0),
					endColor(0.0f,0.0f,0.0f),
					startColor(0.0f,0.0f,0.0f),
					randomFactor(1) { }
		private:
			void initList(int count){
				destroyList();
				this->particles = new Particle[count];
				if(!this->particles){
					LogPrint("Error: Cannot allocate memory for particle engine.");
					destroyList();
				}else{
					this->maxParticles = count;
				}
			}
			void destroyList(){
				if(this->particles)
					delete [] this->particles;
				this->maxParticles = 0;
			}
		public:
			virtual void Init(
					Vector& enginePosition,
					Vector& worldGravity,
					Vector& initForce,
					Color& startColor,
					Color& endColor,
					float engineRadius,
					float particleLifeMax,
					float randomFactor
			){
				initList(256);

				this->position			= enginePosition;
				this->gravity			= worldGravity;
				this->force				= initForce;
				this->radius			= engineRadius;
				this->startColor		= startColor;
				this->endColor			= endColor;
				this->maxParticleLife	= particleLifeMax; // seconds
				this->randomFactor		= randomFactor;
				this->texture.Build("textures/particle.tga");

				Random::Randomize();
			}

			void UpdatePosition(Vector newPosition){
				position = newPosition;
			}
			void UpdateForce(Vector newForce){
				force = newForce;
			}
			void UpdateGravity(Vector newGravity){
				gravity = newGravity;
			}

			virtual void Update(float msec){
				static float seconds;
				static int n;
				static int i;

				seconds = msec/1000.0f;
				for( i= 0; i< maxParticles; i++ ){
					if(particles[i].Valid()){
						particles[i].Update(gravity, seconds);
					} else {
						particles[i].Init(
							position+ Vector(
									Random::Float() * radius*2 - radius,
									Random::Float() * radius*2 - radius,
									Random::Float() * radius*2 - radius
									),
							force+ Vector(
									( Random::Float() * radius*2 - radius )* 50.0f,
									( Random::Float() * radius*2 - radius )* 50.0f,
									( Random::Float() * radius*2 - radius )* 50.0f
									)*randomFactor
								);
						particles[i].Start(
									Random::Float() * maxParticleLife * 0.70f + 0.30f);
					}
				}
			}

			virtual void Render(){
				static int i;
				static Particle *particle;

				static GLboolean lighting;
				lighting = glIsEnabled(GL_LIGHTING);

				if(lighting)  glDisable(GL_LIGHTING);
				glDisable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glPointSize(5);
				glBegin(GL_POINTS);
				for( i =0 ; i<maxParticles; i++){
					particle = &particles[i];

					lifeRatio = particle->Life()/particle->MaxLife();
					finalColor = Interpolate<Color>(startColor,endColor,lifeRatio);
					glColor4f(
						finalColor.r,finalColor.g,finalColor.b,
						Interpolate<float>(1.0f,0.0f,lifeRatio));
					glVertex3fv( particle->Position());
				}
				glEnd();
				glDisable(GL_BLEND);
				if( lighting)  glEnable( GL_LIGHTING);
				glEnable(GL_TEXTURE_2D);
			}

			void Destroy()
			{
				this->texture.Delete();
			}

			virtual	~ParticleEngine(){
				destroyList();
			}
	};


	class FireEngine : public ParticleEngine {
		public:
			FireEngine() : ParticleEngine() {  }
			
			void Render(){
				static int i;
				static float lifeRatio;
				glPushAttrib( GL_ENABLE_BIT);
				glDisable(GL_LIGHTING);
//				glDisable(GL_DEPTH_TEST);
				glDepthMask( GL_FALSE);
				glEnable(GL_BLEND);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE);
				glBindTexture(GL_TEXTURE_2D, this->texture);

/*/
				glBegin(GL_POINTS);
				for( i =0 ; i<maxParticles; i++){
					lifeRatio = particles[i].Life()/particles[i].MaxLife();
					static Color endColor(Color::ColorYellow());
					static Color startColor(Color::ColorOrange());
					static Color finalColor;
					finalColor = Interpolate<Color>(endColor,startColor,lifeRatio);
					glColor4f(
						finalColor.r,finalColor.g,finalColor.b,
						Interpolate<float>(1.0f,0.0f,lifeRatio));
					glVertex3fv(particles[i].Position());
				}
				glEnd();
/*/
				const float w = 0.2f;
				const float h = 0.2f;

				for( i =0 ; i<maxParticles; i++)
				{
					lifeRatio = particles[i].Life()/particles[i].MaxLife();
					static Color endColor(Color::ColorWhite());
					static Color startColor(Color::ColorOrange());
					static Color finalColor;
					finalColor = Interpolate<Color>( endColor, startColor, lifeRatio);
					glColor4f(
						finalColor.r,finalColor.g,finalColor.b,
						Interpolate<float>(1.0f,0.0f,lifeRatio));
					
					MatrixOp::BalloonPoint::Begin( this->particles[i].Position());						

						glBegin(GL_QUADS);
							glTexCoord2f( 0.0f, 0.0f);
							glVertex2f(-w,-h);
							glTexCoord2f( 1.0f, 0.0f);
							glVertex2f( w,-h);
							glTexCoord2f( 1.0f, 1.0f);
							glVertex2f( w, h);
							glTexCoord2f( 0.0f, 1.0f);
							glVertex2f(-w, h);
						glEnd();

					MatrixOp::BalloonPoint::End();
				}
/**/
				glPopAttrib();
				glEnable(GL_LIGHTING);
				glDepthMask( GL_TRUE);
			}

			~FireEngine(){
			}
	};


	class WaterEngine : public ParticleEngine {
		public:
			WaterEngine() : ParticleEngine() {  }
			
			void Update(float msec){
				static float seconds;
				static int n;
				static int i;

				seconds = msec/1000.0f;
				for( i= 0; i< maxParticles; i++ ){
					if(particles[i].Valid()){
						particles[i].Update(gravity, seconds);
					} else {
						particles[i].Init(
							position+ Vector(
									(Random::Float()*2*radius)-radius,
									(Random::Float()*2*radius)-radius,
									(Random::Float()*2*radius)-radius
									),
							force+ Vector(
									Random::Float()*radius,
									Random::Float()*radius,
									Random::Float()*radius
									)
								);
						particles[i].Start(
								(Random::Float()*maxParticleLife*0.75f) + 0.25f);
					}
				}
			}

			void Render(){
				static int i;
				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBegin(GL_POINTS);
				for( i =0 ; i<maxParticles; i++){
					glColor4f(
						0.50f,
						0.75f,
						1.00f,
						Interpolate<float>(1.0f,0.0f,particles[i].Life()/particles[i].MaxLife()));
					glVertex3fv(particles[i].Position());
				}
				glEnd();
				glDisable(GL_BLEND);
				glEnable(GL_LIGHTING);
			}
			~WaterEngine(){
			}
	};
}// namespace DGL

#endif // ___DGL_PARTICLE_H