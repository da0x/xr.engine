/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_system_tooltip.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_SYSTEM_TOOLTIP_H
#define __DUI_SYSTEM_TOOLTIP_H

namespace dui
	{
	namespace system
		{


		class __dui tool_tip :
			public basic::gfx,
			public share::point,         // mouse position
			public graphics::text,
			protected graphics::fill,
			protected graphics::borders
			{
			public: void set_tool_tip( DGL::Color fill, DGL::Color borders, float borderWidth)
						{
						this->set_fill_color(fill);
						this->borders::set_border(borders, borderWidth);
						}

					void paint()
						{
						this->rect::x = this->point::x;
						this->rect::y = this->point::y;
						this->rect::w = DGL::Font::CharWidth() * this->tipSize * (this->text::str.length() + 2);
						this->rect::h = DGL::Font::CharHeight() * this->tipSize;

						this->fill::paint();
						this->borders::paint();
						this->text::paint();
						}

			private: float tipSize;

			public: tool_tip(): tipSize(0)
						{
						}
			};
		}
	}


#endif // __DUI_SYSTEM_TOOLTIP_H

