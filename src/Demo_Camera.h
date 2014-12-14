/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.5 $
	$Date: 2004/07/31 19:22:02 $
	$Id: Demo_Camera.h,v 1.5 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DEMO_CAMERA_H
#define ___DEMO_CAMERA_H

namespace Demo {

	/////////////////////////
	// CameraStage: has its own train and time
	class CameraStage {
		private:
			float					delay;
			float					time;
			float					totalTime;
			class DGL::Train		train;
			class DGL::FadeScreen	fadeIn;
			class DGL::FadeScreen	fadeOut;
			float					fadeOutTime; // needed to start fading at the right time
		public:
			void Init(
					const char *name,
					float delay,
					float time,
					float fadeInTime,
					float fadeOutTime)
			{
				this->train.Load(name);
				this->delay = delay;
				this->totalTime = time;
				this->fadeIn.Init(
								DGL::Color(0.0f,0.0f,0.0f,1.0f),
								DGL::Color(0.0f,0.0f,0.0f,0.0f),
								fadeInTime);
				this->fadeOut.Init(
								DGL::Color(0.0f,0.0f,0.0f,0.0f),
								DGL::Color(0.0f,0.0f,0.0f,1.0f),
								fadeOutTime);
				this->fadeOutTime = fadeOutTime;
			}

			void Update(float msec, class DGL::Camera& camera)
			{
				time += msec;
				class Vector p,d;
				this->train.Update(msec, p, d);
				camera.Set(camera.POSITION, p);
				camera.Set(camera.DIRECTION, d);
				if(time >= delay)
				{
					this->fadeIn.Update(msec);
					if((this->totalTime - this->time)<= this->fadeOutTime)
						this->fadeOut.Update(msec);
				}
			}

			void RenderFade()
			{
/*				if(! this->fadeIn.Render() )
					if(!this->fadeOut.Render())
						// this fixes flickering of the screen
						DGL::Draw2DRect(0,0,640,480,DGL::Color::ColorBlack());
*/			}

			void Destroy()
			{
				this->time = 0;
				this->totalTime = 0;
				this->train.Destroy();
				this->fadeIn.Destroy();
				this->fadeOut.Destroy();
			}

			void Restart()
			{
				this->time = 0;
				this->train.Restart();
				this->fadeIn.Restart();
				this->fadeOut.Restart();
			}

			enum Target {
				TOTAL_TIME
			};

			void Get(Target target, float &f)
			{
				switch(target)
				{
					case TOTAL_TIME:
						f = this->totalTime;
						break;
				}
			}
	};

	/////////////////////////
	// Camera
	class Camera {
		private:
			DGL::Camera		camera;
			static const int	_MaxStages = 1024;
			CameraStage		stages[_MaxStages];
			int				numOfStages;
			int				currentStage;
			float			totalTime;
			float			time;
		public:
			void Init(const char *script)
			{
				this->totalTime = 0;

				DSys::Logger::Print("Loading scene camera file: \"scripts/%s.camera\"", script);
				int file = fs_open(va("scripts/%s.camera",script), "rt");
				if(!file)
				{
					DSys::Logger::Error("Error loading scene camera script");
					return;
				}

				char data[256];
				fs_readln(data, file);
				sscanf(data, "NumOfStages = %d", &this->numOfStages );

				char TrainScript[1024];
				float TotalTime, DelayTime, FadeInTime, FadeOutTime;
				for ( int i =0; i < this->numOfStages; i++)
				{
					fs_readln(data, file);
					sscanf(data, "TrainScript = %s", &TrainScript);
					fs_readln(data, file);
					sscanf(data, "DelayTime = %f", &DelayTime);
					fs_readln(data, file);
					sscanf(data, "TotalTime = %f", &TotalTime);
					fs_readln(data, file);
					sscanf(data, "FadeInTime = %f", &FadeInTime);
					fs_readln(data, file);
					sscanf(data, "FadeOutTime = %f", &FadeOutTime);
					this->stages[i].Init(
										TrainScript,
										DelayTime,
										TotalTime,
										FadeInTime,
										FadeOutTime);
					this->totalTime += TotalTime;
				}
				fs_close(file);
				this->time = 0;
			}

			void Update(float msec)
			{
				if(!this->Done())
				{
					this->time += msec;
					// update the current stage
					float t,ttotal = 0;
					int i;
					for ( i=0; i< this->numOfStages; i++ )
					{
						this->stages[i].Get(CameraStage::TOTAL_TIME, t);
						ttotal += t;
						if( ttotal >= time )
						{
							this->currentStage = i;
							break;
						}
					}
					if( i == this->currentStage)
						this->stages[this->currentStage].Update(msec, this->camera);
				}
			}

			void Setup() const
			{
				if(!this->Done())
					this->camera.Setup();
			}

			void Render()
			{
				if(!this->Done())
					this->stages[this->currentStage].RenderFade();
			}

			void Destroy()
			{
				this->time = 0;
				while(--this->currentStage >= 0)
					this->stages[this->currentStage].Destroy();
			}

			bool Done() const
			{
				return (this->time >= this->totalTime);
			}

			void Restart()
			{
				this->time = 0;
				for ( int i=0; i < this->numOfStages; i++)
				{
					this->stages[i].Restart();
				}
			}
	};
}

#endif // ___DEMO_CAMERA_H