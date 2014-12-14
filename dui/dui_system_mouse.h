/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.5 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_system_mouse.h,v 1.5 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef __DUI_SYSTEM_MOUSE_H
#define __DUI_SYSTEM_MOUSE_H

namespace dui
	{
	namespace system
		{
		
		class __dui mouse
			:
			public share::point,
			public graphics::bitmap
			{

			public: void on_mouse_move( int dx, int dy)
						{
						this->point::x += dx*speed;	Clamp<int>( 0, constant::s_width, this->point::x);
						this->point::y -= dy*speed;	Clamp<int>( 0, constant::s_height, this->point::y);
						}

					void set_mouse_speed(int speed)
						{
						this->speed = speed;
						}

					void get_mouse_speed(int& speed)
						{
						speed = this->speed;
						}

					void on_button_down()
						{
						this->button_down = true;
						}

					void on_button_up()
						{
						this->button_down = false;
						}

					bool is_button_down()
						{
						return this->button_down;
						}

                    
			private: int      speed;
					 bool     button_down;

			public: mouse(): speed(1), button_down(false)
						{
						}

			};
		}
	}

#endif // __DUI_SYSTEM_MOUSE_H


