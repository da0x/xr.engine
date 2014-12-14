/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_basic_gfx.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_BASIC_GFX_H
#define __DUI_BASIC_GFX_H

namespace dui
	{
	namespace basic
		{
		class __dui gfx
			{
			public: virtual void load()
						{// do nothing
						}
					virtual void kill()
						{// do nothing
						}
					virtual void paint()
						{// do nothing
						}
					virtual void update(float)
						{// do nothing
						}
			};
		}
	}

#endif // __DUI_BASIC_GFX_H