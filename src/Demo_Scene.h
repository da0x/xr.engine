/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:22:03 $
	$Id: Demo_Scene.h,v 1.4 2004/07/31 19:22:03 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DEMO_SCENE_H
#define ___DEMO_SCENE_H

namespace Demo {

	///////////////////////
	// Scene class
	class Scene {
		public:
			virtual void	Init() = 0;
			virtual void	Update(float msec) = 0;
			virtual void	Render() = 0;
			virtual void	Destroy() = 0;
			virtual void	Restart() = 0;
			virtual bool	Done() {return false;}
	};
}

#endif // ___DEMO_SCENE_H