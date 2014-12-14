/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:03 $
	$Id: Demo_Effect.h,v 1.3 2004/07/31 19:22:03 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___DEMO_EFFECT
#define ___DEMO_EFFECT

namespace Demo {


	////////////////////////
	// Base Effect class
	class Effect {
	protected:
		float		time;
	public:
		virtual void Restart()
		{
			time = 0;
		}
		virtual void Destroy()
		{
		}
	};



    ////////////////////////
	// FadingLogo
	class FadingLogo : public Effect {
		protected:
			float			totalTime;
			float			delayTime;
			float			alpha;
			DGL::Texture	texture;
			int				width, height;

		public:
			void Init(int w, int h, float totalTime,float delayTime, char*texturePath)
			{
				this->time = 0;
				this->texture.Build(texturePath);
				this->totalTime = totalTime;
				this->delayTime = delayTime;
				this->alpha = 0;
				this->width = w;
				this->height = h;
			}
			inline bool Done()
			{
				return this->time >= this->totalTime+this->delayTime;
			}
			void Update(float msec)
			{
				this->time += msec;

				// check for fading in
				if(this->time <= this->totalTime / 6.0f )
				{
					this->alpha = this->time/(this->totalTime/6.0f);
				}
				else if(this->time <= 4 * this->totalTime /6.0f)
				{
					this->alpha = 1.0f;
				}
				else
				{
					this->alpha = (this->totalTime - this->time) / (2 * this->totalTime / 6.0f);
					if(this->alpha < 0)
						this->alpha = 0.0f;
				}
			}
			void Render()
			{
				DGL::Draw2DRect(
						320 - this->width/2,
						300 - this->height/2,
						this->width,
						this->height,
						this->texture,
						this->alpha);
			}
			void Destroy()
			{
				this->texture.Delete();
			}
	};

	//////////////////////////
	// Poping logo
	class PopingLogo : public FadingLogo {
		public:
			void Render()
			{
				if(alpha)
				{
					DGL::Draw2DRect(
							320 - this->width*this->alpha/2,
							300 - this->height*this->alpha/2,
							this->width*this->alpha,
							this->height*this->alpha,
							this->texture);
				}
			}
	};

}// namespace Horror

#endif // ___DEMO_EFFECT