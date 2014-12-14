/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: DAudio_Main.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DAUDIO_MAIN_H
#define ___DAUDIO_MAIN_H

//#include <fmod.h>
#include "DSys_Var.h"

namespace DAudio {
	extern DSys::Var_int	sv_iSound_MaxChannels;
	extern DSys::Var_int	sv_iSound_Frequency;
	extern DSys::Var_float	sv_fSound_Volume;

	void Init();
	void Update();
	void Shutdown();
}


#endif // ___DAUDIO_MAIN_H