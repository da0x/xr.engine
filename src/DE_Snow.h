/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DE_Snow.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___MCU_SNOW_H
#define ___MCU_SNOW_H

namespace MCU {

	class SnowScene : public Demo::Scene {

		private:

			DGL::Fog				fog;

//			DGL::SkyBox_static		skbox;

			DGL::ModelMilkshape		modelStation;
			DGL::Light				light;

		public:

			SnowScene() : light(GL_LIGHT0)
			{
			}

			void Init()
			{
//				this->fog.SetColor(0.70f, 0.70f, 0.70f, 1.00f);
//				this->fog.SetStartEnd(0, 100);
//				this->fog.Init();
//				this->skbox.InitSkybox("Clouds", 600,600,300);
				this->modelStation.LoadModelData("textures/fence.ms3d");
				this->modelStation.SetPosition( Vector(0, 0, 0 ));
			}

			void Update(float msec)
			{
				this->modelStation.Update(msec);
			}

	
			void Render()
			{
				glClearColor(1,1,1,1);
				glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

//				this->fog.Apply();
				this->modelStation.Render();
			}

			void Destroy()
			{
//				this->skbox.Destroy();

				this->modelStation.Destroy();
			}

			void Restart()
			{
			}

	};

}// namespace MCU

#endif // ___MCU_SNOW_H