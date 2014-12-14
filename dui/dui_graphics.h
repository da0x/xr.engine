/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_graphics.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_GRAPHICS_H
#define __DUI_GRAPHICS_H

#pragma message ("dui_graphics.h: make this independednt")
#include "../src/dshared.h"
#include "../src/dsys.h"
#include "../src/dgl.h"

namespace dui
	{
	namespace graphics
		{
		class __dui borders :
			public basic::gfx,
			public share::rect
			{
			public: void set_border(DGL::Color color, float lineWidth)
						{
						this->color = color;
						this->lineWidth = lineWidth;
						}
					void get_border(DGL::Color& color, float lineWidth) const
						{
						color = this->color;
						lineWidth = this->lineWidth;
						}
					void paint()
						{
						glDisable(GL_TEXTURE_2D);
						this->color.MakeCurrent();
						glLineWidth(this->lineWidth);
						glBegin(GL_LINE_STRIP);				
						glVertex2i( this->rect::x,                 this->rect::y);
						glVertex2i( this->rect::x + this->rect::w, this->rect::y);
						glVertex2i( this->rect::x + this->rect::w, this->rect::y + this->rect::h);
						glVertex2i( this->rect::x,                 this->rect::y + this->rect::h);
						glVertex2i( this->rect::x,                 this->rect::y);
						glEnd();
						glLineWidth(1.0f);
						glEnable(GL_TEXTURE_2D);
						}
			private: DGL::Color color;
						float		lineWidth;

			public: borders(): color(1.0f,1.0f,1.0f,1.0f),
								lineWidth(0.3f)
						{
						}
			};

		class __dui bitmap :
			public basic::gfx,
			public share::rect
			{
			public: void set_bitmap( DGL::Texture texture )
						{
						this->texture = texture;
						}
					void get_bitmap( DGL::Texture& texture )
						{
						texture = this->texture;
						}
					void paint()
						{
						glBindTexture( GL_TEXTURE_2D, this->texture);

						glBegin(GL_QUADS);
						glTexCoord2f(0.0f,0.0f);		glVertex2d( this->x,         this->y);
						glTexCoord2f(1.0f,0.0f);		glVertex2d( this->x+this->w, this->y);
						glTexCoord2f(1.0f,1.0f);		glVertex2d( this->x+this->w, this->y+this->h);
						glTexCoord2f(0.0f,1.0f);		glVertex2d( this->x,         this->y+this->h);
						glEnd();
						}
			private: DGL::Texture  texture;
			};

		class __dui text :
			public basic::gfx,
			public share::point // start point of the text
			{
			public: void set_text( string str)
						{
						this->str = str;
						}
					void set_text_font( DGL::Font& font)
						{
						this->font = font;
						}
					void paint()
						{// style and colors are applied to the gobal font
						this->font.Print( this->point::x, this->point::y, this->str.c_str() );
						}

			protected: string        str;
					   DGL::Font     font;

			public: text(): str("")
						{
						}
			};

		class __dui fill :
			public basic::gfx,
			public share::rect
			{
			public: void set_fill_color(DGL::Color color)
						{
						this->color = color;
						}

					void paint()
						{
						glPushAttrib(GL_ENABLE_BIT);
						glDisable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

						this->color.MakeCurrent();
						glBegin(GL_QUADS);
						glVertex2i(this->rect::x,                 this->rect::y);
						glVertex2i(this->rect::x + this->rect::w, this->rect::y);
						glVertex2i(this->rect::x + this->rect::w, this->rect::y + this->rect::h);
						glVertex2i(this->rect::x,                 this->rect::y + this->rect::h);
						
						glEnd();
						glPopAttrib();
						}

			private: DGL::Color color;

			public: fill(): color(0.0f,0.0f,0.0f,0.0f)
						{
						}
			};

		}
	}

#endif // __DUI_GRAPHICS_H

