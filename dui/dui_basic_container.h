/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.6 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_basic_container.h,v 1.6 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef __DUI_BASIC_CONTAINER_H
#define __DUI_BASIC_CONTAINER_H

namespace dui
	{
	namespace basic
		{
		template <class element> class __dui container
			{
			protected: typedef element                             * element_ptr;
					   typedef class list<element_ptr>               element_list;
					   typedef class element_list::iterator          iterator;

			public: void register_element( element_ptr elem )
						{
						this->elements.push_back( elem );
						}
					
					iterator begin()
						{
						return this->elements.begin();
						}
					iterator end()
						{
						return this->elements.end();
						}

					// commands
					void show()
						{
						std::for_each(this->begin(), this->end(), /*std::bind2nd( */std::mem_fun1( element::show)/*, 0)*/);
						}

                    void hide()
						{
						std::for_each(this->begin(), this->end(), /*std::bind2nd( */std::mem_fun1( element::hide)/*, 0)*/);
						}

					void disable()
						{
						std::for_each(this->begin(), this->end(), /*std::bind2nd( */std::mem_fun1( element::disable)/*, 0)*/);
						}

					void enable()
						{
						std::for_each(this->begin(), this->end(), /*std::bind2nd( */std::mem_fun1( element::enable)/*, 0)*/);
						}
					
					// gfx
/*					void load()
						{
						std::for_each(this->begin(), this->end(), std::mem_fun1( element::load));
						}
					
					void kill()
						{
						std::for_each(this->begin(), this->end(), std::mem_fun1( element::kill));
						}
*/
			protected: element_list  elements;

			protected: 
			};
		}
	}

#endif // __DUI_BASIC_CONTAINER_H