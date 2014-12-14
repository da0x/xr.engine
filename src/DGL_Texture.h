/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Texture.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DGL_TEXTURE_H
#define ___DGL_TEXTURE_H

namespace DGL {
	/*
	=============================================================

		TEXTURES

	=============================================================
	*/

	class Texture {
		public:
			/////////////////
			// Member Classes
			class Filter;
			class Image;
			class ImageBMP;
			class ImageTGA;
			class ImageJPG;

			/////////////////
			// Public Methods: Build/Delete
			void Build(const char *filename, Filter filter = auxFilter);
			void Delete();

			/////////////////
			// Screen Shot
			static void _ScreenShot ( int w, int h);

			/////////////////
			// operator GLuint
			inline operator GLuint () const
			{
				return this->glTexture;
			}

			inline const GLuint* operator &() const
			{
				return &this->glTexture;
			}

			inline Texture& operator = ( const Texture& right)
			{
				this->glTexture = right.glTexture;
				return *this;
			}

			Texture() : glTexture(0)
			{
			}

			~Texture(){
				this->glTexture = 0;
//				delete this->image;
				this->image = NULL;
			}


		public:

			/////////////////////////////////////
			// Filter : filter defining object
			class Filter {
				public:
					enum FilterName{
						NEAREST		= 0x0001,
						LINEAR		= 0x0002,
						BILINEAR	= 0x0003,
						TRILINEAR	= 0x0004
					};

					Filter(int FilterName = auxDefault, bool noRepeat = false);
					Filter(Filter&);

						/***************************************************\
						/  SetParametrs :									\
						/	Supported Parameters and there default values	\
  						/	GL_TEXTURE_MAG_FILTER							\
						/	GL_TEXTURE_MIN_FILTER							\
						/	GL_TEXTURE_WRAP_S								\
						/	GL_TEXTURE_WRAP_T								\
						/***************************************************/

					void SetParameter(GLenum target, GLenum pname, GLint param);
					GLint GetParameter(GLenum pname);

					///////////////////////////
					// Use : sets the parameters to opengl's current texture
					void Use() const;

					///////////////////////////
					// IsMipmap : Filter requires using mipmaps or normal texture.
					bool IsMipmap() const;

					///////////////////////////
					// auxDefault : Default filter
					static const int auxDefault = FilterName::TRILINEAR;
				private:
					bool	textureGenMipmap;
					int		textureMagFilter;
					int		textureMinFilter;
					int		textureWarpS;
					int		textureWarpT;
			};


			////////////////////////////////////////
			// Image : Image loading base class
			class Image {
				public:
                    Image();
					~Image();

					virtual void Load(const char *filename) = 0;
					virtual void Free();

					void Resize(float width, float height = -1);
					void Scale(float f);
										

					enum Component
					{
						Red,
						Green,
						Blue,
						Alpha
					};

					inline unsigned char operator() (int x, int y, Component c) const
						{
							return data[(x * this->components + y * this->components * this->width) + c];
						}

					inline unsigned char* operator() (int x, int y, unsigned char *buffer) const
						{
							int index = x * this->components + y * this->components * this->width;
							buffer[Red] = this->data[ index + Red ];
							buffer[Green] = this->data[ index + Green ];
							buffer[Blue] = this->data[ index + Blue ];
							if(this->components > 3)
								buffer[Alpha] = this->data[ index + Alpha ];
							return buffer;
						}

					inline int Width() const
						{
							return this->width;
						}
					inline int Height() const
						{
							return this->height;
						}

					enum GetParam
					{	FORMAT, WIDTH, HEIGHT, COMPONENTS };

					inline int Get(GetParam param)
					{
						switch (param)
						{
						case FORMAT:
							return this->format;
						case WIDTH:
							return this->width;
						case HEIGHT:
							return this->height;
						case COMPONENTS:
							return this->components;
						}
						return 0;
					}

					inline unsigned char * Data(){ return this->data; }

				protected:
					int				format;			// GL_RGBA | GL_RGB
					int				width;			// image width (in pixels)
					int				height;			// image height (in pixels)
					int				components;		// components per pixels
					unsigned char	*data;			// image data
			};

			class ImageBMP :
				public Image
			{
				public: void Load(const char* filename);
			};

			class ImageTGA :
				public Image
			{
				public: void Load(const char* filename);
			};

			class ImageJPG :
				public Image
			{
				public: void Load(const char* filename);
			};
		
		private:
			GLuint	glTexture;
			Image	*image;
			
			static	Filter auxFilter;

			struct TargaHeader {
				unsigned char 	idLength, colormapType, imageType;
				unsigned short	colormapIndex, colormapLength;
				unsigned char	colormapSize;
				unsigned short	xOrigin, yOrigin, width, height;
				unsigned char	pixelSize, attributes;
			};

			static unsigned int _buildTexture(GLenum target, GLint components, GLint width, GLint height, GLenum format, GLenum type, const void  *data, Filter filter);
	};
}

#endif // ___DGL_FRUSTUM_H
