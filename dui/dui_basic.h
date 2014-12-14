/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_basic.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_BASIC_H
#define __DUI_BASIC_H

namespace dui
	{
	namespace basic
		{
		class __dui                          gfx;
		class __dui                          object;
		template <class element> class __dui container;

		class __dui                          window;
		}
	}

#include "dui_basic_gfx.h"
#include "dui_basic_object.h"
#include "dui_basic_container.h"
#include "dui_basic_window.h"

#endif // __DUI_BASIC_H