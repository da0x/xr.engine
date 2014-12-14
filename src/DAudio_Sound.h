/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DAudio_Sound.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DAUDIO_SOUND_H
#define ___DAUDIO_SOUND_H

//#include <FMOD.h>

namespace DAudio {

	class Sound {
		protected:
			virtual void setExtraParameters() = 0;
		public:
			void Load(const char *filename){
#if 0
				DSys::Logger::Print("Loading sound sample: \"%s\" ...", filename);
				this->mod = FSOUND_Sample_Load(FSOUND_FREE, filename, this->inputMode, 0);
				if(!this->mod)
				{
					DSys::Logger::Error("Cannot load sound sample...");
					return;
				}
#endif
			}

			void Play()
			{
#if 0
				this->channel = FSOUND_PlaySound(FSOUND_FREE, this->mod);
				this->setExtraParameters();
#endif
			}

			bool IsPlaying()
			{
#if 0
				return (bool)FSOUND_IsPlaying(this->channel);
#else
			return true;
#endif
			}

			void Stop()
			{
#if 0
				if(this->IsPlaying())
					FSOUND_StopSound(this->channel);
				this->channel = -1;
#endif
			}

			void Pause(bool pause)
			{
#if 0
				FSOUND_SetPaused(this->channel, pause);
#endif
			}

			void Destroy()
			{
#if 0
				this->Stop();
				FSOUND_Sample_Free(this->mod);
#endif
			}

		protected:
//			FMOD_SOUND		*mod;
			unsigned int	inputMode;
			int				channel;
		public:
			Sound(bool looping = false) :
#if 0
			  	mod(NULL),
				inputMode(FSOUND_HW3D),
#endif
				channel(-1)
			{
#if 0
				if(looping)
					this->inputMode |= FSOUND_LOOP_NORMAL;
#endif
			}
	};


	///////////////////////////
	// 2D Sound

	class Sound2D : public Sound {
		public:
			Sound2D(bool looping = false)
			{
#if 0
				this->inputMode = FSOUND_2D;
				if(looping)
					this->inputMode |= FSOUND_LOOP_NORMAL;
#endif
			}
		protected:
			void setExtraParameters()
			{
#if 0
				FSOUND_SetSurround(this->channel, TRUE);
#endif
			}
	};


	/////////////////////////////
	// 3D Sound
	class Sound3D : public Sound {
		private:
			Vector	position;
			Vector	velocity;
		public:
			Sound3D (bool looping = false) : Sound(looping), position(0,0,0), velocity(0,0,0)
			{
			}

			void SetDistances(float minDistance, float maxDistance)
			{
#if 0
				FSOUND_Sample_SetMinMaxDistance(this->mod, minDistance, maxDistance);
				this->position = position;
#endif
			}

			void Update(float msec, Vector position)
			{
#if 0
				this->velocity = (position - this->position) * 1000.0f/msec;
				this->position = position;
#endif
			}

		protected:
			void setExtraParameters()
			{
#if 0
				FSOUND_SetSurround(this->channel, TRUE);
				FSOUND_3D_SetAttributes(this->channel, this->position, this->velocity);
#endif
			}
	};

}


#endif // ___DAUDIO_SOUND_H
