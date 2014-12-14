/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.5 $
	$Date: 2003/10/27 04:00:30 $
	$Id: dui_basic_window.h,v 1.5 2003/10/27 04:00:30 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_BASIC_WINDOW_H
#define __DUI_BASIC_WINDOW_H


namespace dui
	{
	namespace basic
		{

		class window :
			public object,
			public container<object>
			{
			protected: typedef container<object>::iterator   iterator;

			public: virtual void load()
						{
						this->gfx::load();
//						this->container<object>::load();
						}

					virtual void kill()
						{
						this->gfx::kill();
//						this->container<object>::kill();
						}
					
					virtual void update(float msec)
						{
						this->gfx::update(msec);
						for(container<object>::iterator iter = this->elements.begin();
							iter != this->elements.end();
							iter ++ )
							{
							(*iter)->update(msec);
							}
						}

					virtual void paint()
						{
						this->gfx::paint();
						for(iterator iter = this->elements.begin();
							iter != this->elements.end();
							iter ++ )
							{
							if( (*iter)->is_visible() )
								(*iter)->paint();
							}
						}

					virtual void show()
						{
						this->object::show();
						}

					virtual void hide()
						{
						this->object::hide();
						}

					virtual bool is_visible()
						{
						return this->object::is_visible();
						}

					virtual void disable()
						{
						this->object::disable();
						}

					virtual void enable()
						{
						this->object::enable();
						}

					virtual bool is_enabled()
						{
						return this->object::is_enabled();
						}

			public: virtual void on_click( const share::point&  mouse_position )
						{ // fire the event
						for(iterator iter = this->elements.begin();
							iter != this->elements.end();
							iter ++ )
							{
							if( (*iter)->rect::point_on_rect( mouse_position ) )
								{
								(*iter)->on_click( mouse_position );
								break;
								}							
							}
						}

					virtual void on_mouse_move( const share::point& mouse_position )
						{
						if( this->drag )
							{
							this->rect::x += mouse_position.x - this->drag_home.x;
							this->rect::y += mouse_position.y - this->drag_home.y;
							this->drag_home = mouse_position;
							}
						}

					virtual void on_mouse_down( const share::point&  mouse_position )
						{
						for(iterator iter = this->elements.begin();
							iter != this->elements.end();
							iter ++ )
							{
							if( this->rect::point_on_rect( mouse_position ) )
								{
								(*iter)->on_mouse_down( mouse_position );
								return; // skip dragging
								}
							}

						this->drag = true;
						this->drag_home = mouse_position;
						}

					virtual void on_mouse_up()
						{
						this->drag = false;
						}

					virtual void on_mouse_click();
					virtual void on_key_down();
					virtual void on_key_up();
					virtual void on_key_click();

			private: bool           drag;
					 share::point   drag_home;

			public: window() : drag(false), drag_home(0,0)
						{
						}
			};
		}
	}

#endif // __DUI_BASIC_WINDOW_H