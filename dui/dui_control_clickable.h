/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_control_clickable.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_CONTROL_CLICKABLE_H
#define __DUI_CONTROL_CLICKABLE_H

namespace dui
	{
	namespace control
		{		
		class __dui events : public basic::object
			{
			public: virtual void on_click()
						{ // do nothing
						}
					virtual void on_mouse_move( share::point )
						{ // do nothing
						}
					virtual void on_mouse_down()
						{ // do nothing
						}
					virtual void on_mouse_up()
						{ // do nothing
						}
					virtual void on_key_down()
						{ // do nothing
						}
					virtual void on_key_up()
						{ // do nothing
						}
			};
		}
	}


#endif // __DUI_CONTROL_CLICKABLE_H
