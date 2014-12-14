/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_TextImage.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#pragma once
#ifndef ___DGL_TEXTIMAGE_H
#define ___DGL_TEXTIMAGE_H


namespace DGL {

	class TextImage {

		Texture::ImageJPG	image;
		char				textBuffer[1024];
		int					textLength;
		bool				random;

		int					width;

		struct Element {
			Color	color;
			char	charecter;
		};

		Element				*elements;
	public:

		TextImage( const char *JPGfile, const char *fmt, int width, bool random)
		{
			strcpy( this->textBuffer, fmt);
			this->textLength = strlen( this->textBuffer);
			this->random = random;
			this->width = width;

			try
			{
				this->image.Load(JPGfile);
				this->image.Resize(width);
			} catch (Daher::Exception& ex){
				DSys::Logger::Error("Text Image cannot load the image: %s", ex.What());
			}

			this->elements = new Element[this->image.Width() * this->image.Height()];

			int s = 0;
			for ( int j=0; j< this->image.Height(); j++)
			{
				for ( int i=0; i< this->image.Width(); i++)
				{
					this->elements[i + j * this->image.Height()].charecter =
						this->random
							?
							this->textBuffer[Random::Int() % this->textLength]
							:
							this->textBuffer[s++ % this->textLength];

					this->elements[i + j * this->image.Height()].
						color.Set(	this->image( i, j, this->image.Red),
									this->image( i, j, this->image.Green),
									this->image( i, j, this->image.Blue));
				}
			}
		}

		void Render()
		{
			glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);
			for(int j=0; j< this->image.Height(); j++)
			{
				for(int i=0; i< this->image.Width(); i++)
				{
					int index = i + j* this->image.Height();
					DGL::Font::Print3D(
						i*10,j*10,0,
						"%c",
						1,
						DGL::Font::STYLE_LEFT, 
						this->elements[index].color,
						0,
						this->elements[index].charecter);
				}
			}
			glPopAttrib();
		}


	};

}

#endif // ___DGL_TEXTIMAGE_H