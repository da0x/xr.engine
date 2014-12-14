/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_basic_object.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_BASIC_OBJECT_H
#define __DUI_BASIC_OBJECT_H


namespace dui
	{
	namespace basic
		{
		
		class __dui object
			:
			public dui::share::rect,
			public dui::basic::gfx
			{
			public: virtual void on_click( const share::point& );
					virtual void on_mouse_move( const share::point& );
					virtual void on_mouse_down( const share::point& );
					virtual void on_mouse_up();
					virtual void on_mouse_click();
					virtual void on_key_down();
					virtual void on_key_up();
					virtual void on_key_click();

			public: void show();
					void hide();
					bool is_visible();
					void disable();
					void enable();
					bool is_enabled();

			protected: bool     visible;
			protected: bool     enabled;
			protected: bool     mouseDown;


			public: object();
			};

		}
	}


#endif // __DUI_BASIC_OBJECT_H
