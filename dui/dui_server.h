/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_server.h,v 1.4 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_SERVER
#define __DUI_SERVER


namespace dui
	{

	class __dui server
		{
		typedef list<basic::window *>         window_list;
		typedef window_list::iterator         iterator;
		typedef window_list::reverse_iterator reverse_iterator;

		public: virtual void OnInit()
					{
					}
				virtual void OnDestroy()
					{
					}

		public: void initalize();
				void shutdown();

				void update(float msec)
					{
					if(this->active)
						{
						this->do_update(msec);
						}
					}
				void render()
					{
					if(this->active)
						{
						this->do_render();
						}
					}
				void activate()
					{
					this->active = true;
					}
				void deactivate()
					{
					this->active = false;
					}

		private: void do_update(float msec)
					 {
					 const int dx = DSys::Input::MouseXDelta();
					 const int dy = DSys::Input::MouseYDelta();
					 const bool mouse_char = DSys::Input::MouseChar( 0 );
					 const bool mouse_down = DSys::Input::MouseDown( 0 );

					 this->mouse.on_mouse_move(dx,dy);
					 if( this->mouse.is_button_down() && ! mouse_down )
						 {
						 this->mouse.on_button_up();

						 // fire event to the topmost window
						 (*this->windows.rbegin())->on_mouse_up();
						 }

					 if( mouse_char )
						 {
						 this->mouse.on_button_down();
                         
						 // fire mouse event to the topmost window
						 for(reverse_iterator iter = this->windows.rbegin();
							 iter != this->windows.rend();
							 iter ++ )
							 {

							 if( (*iter)->rect::point_on_rect( this->mouse ) )
								 {
								 if( iter != this->windows.rbegin() )
									 { // raise the window
									 this->raise( *iter );
									 (*iter)->on_mouse_down(this->mouse);
									 }
								 else
									 { // let the window recive the click
									 (*iter)->on_click( this->mouse );
									 }
								 break;
								 }
							 }
						 }
					 
					 // finally, update all windows
					 for(iterator iter = this->windows.begin();
						 iter != this->windows.end();
						 iter ++ )
						 {
						 if(dx || dy)
							 (*iter)->on_mouse_move( this->mouse );

						 (*iter)->update(msec);
						 }
					 }
				 void do_render()
					 { // TODO: enable ortho matrix/disable lighting.. etc
					 for(iterator iter = this->windows.begin();
						 iter != this->windows.end();
						 iter ++ )
						 {
						 if( (*iter)->is_visible() )
							 (*iter)->paint();
						 }
					 }

		private: void raise( basic::window * window )
					{// remove then push_back ...
					this->windows.remove( window );
					this->windows.push_back( window );
					}

		private: bool               active;
				 system::mouse      mouse;
				 system::tool_tip   tooltip;
				 window_list        windows;

		public: server()
					:
					active(false)
						{
						}

		};
	}

#endif // __DUI_SERVER