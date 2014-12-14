/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/09/11 05:16:28 $
	$Id: DGL_Font.h,v 1.4 2004/09/11 05:16:28 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DGL_FONT_H
#define ___DGL_FONT_H


#include "DGL_Color.h"

namespace DGL {

	class Texture;
		
	/*
	=================================================================

	FONTS
	
	=================================================================
	*/

	class Font {
		public:
			//
			// Interface
			//
			void Create(const char *name);			
			void Print(int x, int y, const char *fmt, ...) const;
			void Print3D( Vector pos, const char *fmt, ...) const;
			void SetColor(Color &color) { this->color = color; }
			void SetSize(float size) { this->size = size; }
			enum EStyle {
				STYLE_LEFT		= 0x00000001,
				STYLE_RIGHT		= 0x00000002,
				STYLE_CENTER	= 0x00000004,
				STYLE_SHADOWS	= 0x00000008
			};
			void SetStyle(int style) { this->style = style; }
			
			inline Font& operator = (Font& f)
			{
				this->size = f.size;
				this->style = f.style;
				this->color = f.color;
				this->font = f.font;
				return *this;
			}

			Font() :
				size(1),
				style(STYLE_LEFT|STYLE_SHADOWS),
				color(1.0f,1.0f,1.0f),
				font(0) { }

		private:
			float			size;
			int				style;
			Color			color;
			int				font;

		public:
			static void Init(void);
			static void Kill(void);
			static int	CreateFont(const char *name);
			static void Print2D( int x, int y, const char *fmt, float size, int attribs, const float* color, int font, ...);
			static void Print3D( float x, float y, float z, const char *fmt, float size, int attribs, const float* color, int font,	...);
			static float CharWidth();
			static float CharHeight();
		private:
			static bool			valid;
			static GLuint		charList;
			static const int	MAX_FONTS	= 0x0100;
			static Texture		fontTexture[MAX_FONTS];
			static char			fontTextureName[MAX_FONTS][64];
			static int			currentFree;
			static float		orthoMatrix[16];
			static bool			orthoMatrixValid;
			static float		shadowColor[4];

			static void GenerateFontLists(GLuint& ListID, float char_width,float char_height, float xspacing);
			static void PrintToOrtho(int x,int y, const char *fmt, int fmtMax, int charindex, const float *color, float scale);
			static void PrintToScene(float x,float y,float z, const char *fmt, int fmtMax, int charindex, const float *color, float scale);
	};
}


#endif // ___DGL_FONT_H