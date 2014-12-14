//---------------------------------------------------------------------------
#ifndef fxTextureH
#define fxTextureH
//---------------------------------------------------------------------------

#include <malloc.h>
#include <string.h>
#include <graphics.hpp>

class fxTexture
	{

	protected:

		char * name;

	public:
		fxTexture()
			{
			mem = NULL;
			name =(char*)malloc(256);
			strcpy(name, "default texture");

			clampu=clampv=false;
			mipmap=true;
			}

		~fxTexture()
			{
			if (mem != NULL) free(mem);
			free(name);
			}

		// this memory holds a copy of the image in 32 bit rgba format
		unsigned char * mem;
		// width of the texture (must be 2^n, n=0,1,2,4,8,16,...)
		int width;
		// height of the texture (must be 2^n, n=0,1,2,4,8,16,...)
		int height;
		// bit depth of the texture (must be 1,2,3 or 4)
		int bpp;

		// clamp flags for u and v directions
		bool clampu;
		bool clampv;

		// generate mipmaps?
		bool mipmap;

//		bool Load( char * filename);

                void LoadFromBmp(Graphics::TBitmap * bmp);
		void SaveBMP(char* rgb_file, char * alpha_file);
	};


#endif
