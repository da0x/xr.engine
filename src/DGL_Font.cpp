/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/09/11 05:16:28 $
	$Id: DGL_Font.cpp,v 1.4 2004/09/11 05:16:28 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


/*
TODO List:
- ...
*/

#include "DGL_Main.h"
#include "DGL_Font.h"
#include "DGL_Texture.h"

#define CHAR_HEIGHT		10.0f
#define CHAR_WIDTH		10.0f
#define CHAR_XSPACING	7.75f

namespace DGL {

	//
	// Interface
	//

	void Font::Create(const char *name)
	{
		this->font = Font::CreateFont(name);
	}

	void Font::Print( int x, int y, const char *fmt, ...) const
	{
		va_list arg;
		char	text[256];
		va_start( arg, fmt);
		vsprintf( text, fmt, arg);
		Font::Print2D(	x,
						y,
						text,
						this->size,
						this->style,
						this->color,
						this->font);
		va_end(arg);
	}

	void Font::Print3D( Vector pos, const char *fmt, ...) const
	{
		va_list arg;
		char	text[256];
		va_start( arg, fmt);
		vsprintf( text, fmt, arg);

		Font::Print3D(pos.x_(),pos.y_(),pos.z_(),text,this->size,this->style,this->color,this->font);
		va_end(arg);
	}


	//
	// Background
	//

	bool			Font::valid	= false;
	GLuint			Font::charList;
	Texture			Font::fontTexture[MAX_FONTS];
	char			Font::fontTextureName[MAX_FONTS][64];
	int				Font::currentFree;
	float			Font::orthoMatrix[16];
	bool			Font::orthoMatrixValid;
	float			Font::shadowColor[4] = {0.00f,0.00f,0.00f,1.00f};


	/*
	---------------------
	Generate Font Lists
	---------------------
	*/
	
	void Font::GenerateFontLists(GLuint& ListID, float char_width,float char_height, float xspacing){
		DGL::LogPrint("Creating GL List For 256 Character...", char_width, char_height);
		float	s1;
		float	t1;
		float	s2;
		float	t2;
		s1=t1=s2=t2= 0.0f;

		float	height = char_height/ 2.0f;
		float	width =	char_width/ 2.0f;
		ListID= glGenLists(256);	// generate storage for the lists
		t1= 1.0f;	t2= t1+ ((16.0f) / (256.0f));
		for(int j= 16; j> 0; j--){
			t1-= ((16.0f) / (256.0f));	t2= t1+ ((16.0f) / (256.0f));
			glColor4f(1.0f,0.0f,0.0f,1.0f);
			for(int i=0; i<16; i++){
				glTranslatef(2.0f,0.0f,0.0f);
				glNewList( ListID++, GL_COMPILE);
				glBegin(GL_QUADS);
					glTexCoord2f(s1,t1);	glVertex3f(-height,-width,0.0f);
					glTexCoord2f(s2,t1);	glVertex3f( height,-width,0.0f);
					glTexCoord2f(s2,t2);	glVertex3f( height, width,0.0f);
					glTexCoord2f(s1,t2);	glVertex3f(-height, width,0.0f);
				glEnd();
				glTranslated(xspacing,0,0);
				glEndList();
				s1+= ((16.0f) / (256.0f));s2= s1+ ((16.0f) / (256.0f));
			}
		}
		ListID-= (GLuint)(256);		// reset char to the begining of the lists
	}

	/*
	--------------------
	Init Fonts
	--------------------
	*/
	void Font::Init(void){
		DGL::LogPrint("Initializing Font");

		// now create gl lists for small and large font
		GenerateFontLists(charList, CHAR_WIDTH, CHAR_HEIGHT, CHAR_XSPACING);
		currentFree = 0;
		valid= true;
	}
	
	/*
	--------------------
	Kill Fonts
	--------------------
	*/
	void Font::Kill(void){
		DGL::LogPrint("Deleting Font GL Lists ...");
		glDeleteLists( charList, 256);
		while(currentFree--){
			fontTexture[currentFree].Delete();
		}
		currentFree = 0;
		valid= false;
	}
	
	/*
	--------------------
	Create Font
	--------------------
	*/
	int Font::CreateFont(const char *name){
		if(currentFree >= MAX_FONTS){
			DGL::LogError("MAX_FONTS reached.");
			return 0;
		}

		// check if the texture is already loaded
		for(int i=0; i< currentFree; i++){
			if(!strcmpi(name, fontTextureName[i])){
				DGL::LogPrint("Font \"%s\" already loaded, using current.",name);
				return i;
			}
		}

		char TexName[MAX_PATH];
		sprintf(TexName, "textures/fonts/%s.tga", name);
		DGL::LogPrint("Creating Font %i \"%s\"", currentFree, name);
		fontTexture[currentFree].Build(TexName);
		strcpy(fontTextureName[currentFree], name);
		return currentFree++;
	}
    
	/*
	=======================================

	2D Printing

	=======================================
	*/
	void Font::PrintToOrtho(
			int				x,
			int				y,
			const char		*fmt,
			int				fmtMax,
			int				charindex,
			const float*	color,
			float			scale
	){
		if(!valid)	return;
		GLuint ch=0;

		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);	glPushMatrix(); glLoadIdentity();
		if(!orthoMatrixValid){
			glOrtho(0,640,0,480,-100,100);
			glGetFloatv ( GL_PROJECTION_MATRIX, orthoMatrix);
			orthoMatrixValid = true;
		} else {
			glLoadMatrixf(orthoMatrix);
		}
		glMatrixMode(GL_MODELVIEW);		glPushMatrix(); glLoadIdentity();
		glLoadIdentity();
		glBindTexture( GL_TEXTURE_2D, fontTexture[charindex]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4fv(color);
		glTranslated(x,y,0);
		glListBase(charList);
		glScalef(scale,scale,scale);
		glCallLists(fmtMax, GL_UNSIGNED_BYTE, fmt);
		glColor4f(1,1,1,1);
		glMatrixMode(GL_PROJECTION);	glPopMatrix();
		glMatrixMode(GL_MODELVIEW);		glPopMatrix();
		glPopAttrib();
	}
        
	void Font::Print2D(
			int					x,
			int					y,
			const char			*fmt,
			float				size,
			int					attribs,
			const float*		color,
			int					font,
			...
	){
		static int		xspacing = CHAR_XSPACING;
		static char		buf[1024*24];		// use large buffer
		static int		len;
		static va_list	ap;

		// if no fonts are available or if out of screen skip printing
		if( !currentFree || x < 0 || x > 640 || y < 0 || y > 480) return;

		va_start( ap, font);
		vsprintf( buf, fmt, ap);
		va_end( ap);

		len = strlen( buf);

		if ( attribs & STYLE_CENTER){
			x-= ( len * ( xspacing/2 ) + xspacing/2 ) * size;
		} else {
			if( attribs & STYLE_RIGHT){
				x-= (len)* xspacing* size;
			}
		}
		Clamp<int>(0, currentFree-1, font);
		shadowColor[3] = color[3];
		if( attribs & STYLE_SHADOWS ){
			PrintToOrtho(x+1,y-1,buf,len,font,shadowColor,size);
		}
		PrintToOrtho(x,y,buf,len,font,color,size);
	}




	/*
	=======================================
	
	  3D Printing
	
	=======================================
	*/


	void Font::PrintToScene (
			float			x,
			float			y,
			float			z,
			const char		*fmt,
			int				fmtMax,
			int				charindex,
			const float*	color,
	 		float			scale
	){
		if(!valid)	return;
		GLuint ch=0;	

		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		
		glPushMatrix();
	
		glBindTexture( GL_TEXTURE_2D, fontTexture[charindex]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4fv(color);
	
		glTranslatef(x,y,z);
		glListBase(charList);
		glScalef(scale,scale,scale);
		glCallLists(fmtMax, GL_UNSIGNED_BYTE, fmt);
		glColor4f(1,1,1,1);
		glPopMatrix();
		glPopAttrib();
	}

	void Font::Print3D(
			float				x,
			float				y,
			float				z,
			const char			*fmt,
			float				size,
			int					attribs,
			const float*		color,
			int					font,
		...
	){
		static int		xspacing = CHAR_XSPACING;
		static char		buf[1024*24];		// use large buffer
		static int		len;
		static va_list	ap;
	
		va_start(ap,font);
		vsprintf( buf, fmt, ap);
		va_end(ap);

		len = strlen(buf);
	
			if ( attribs & STYLE_CENTER){
			x-= len* (xspacing/2)* size;
		} else {
			if( attribs & STYLE_RIGHT){
				x-= len* xspacing* size;
			}
		}
		Clamp<int>(0, currentFree-1, font);
		PrintToScene(x,y,z,buf,len,font,color,size);
	}

	float Font::CharWidth(){return CHAR_XSPACING;}
	float Font::CharHeight(){return CHAR_HEIGHT;}

}//namespace DGL
