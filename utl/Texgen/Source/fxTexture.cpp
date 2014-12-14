//---------------------------------------------------------------------------
#include "fxTexture.h"
//---------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

int GetRed(TColor c)
{
return (c & 0x000000ff);
}

int GetGreen(TColor c)
{
return ((c & 0x0000ff00) >> 8);
}

int GetBlue(TColor c)
{
return ((c & 0x00ff0000) >> 16);
}


void fxTexture::LoadFromBmp(Graphics::TBitmap * bmp)
{
bpp = 3;

width = bmp->Width;
height = bmp->Height;

mem = (char*)malloc(width * height *3);

struct color24
        {
	char r,g,b;
	};

for (int i = 0; i< height; i++)
	{
	for (int v = 0; v< width; v++)
		{
		color24 * c = (color24*)(mem+(i*width + v)*sizeof(color24));

                TColor bmp_c = bmp->Canvas->Pixels[v][i]; 

                c->r = GetRed(bmp_c);               
                c->g = GetGreen(bmp_c);
                c->b = GetBlue(bmp_c);
		}
	}


}

void fxTexture::SaveBMP(char * rgb_file, char * alpha_file)
{
FILE * rgb;
FILE * alpha;
	
if (rgb_file)
	{
	// save the rgb channel to file

	int line_numbytes = (width*3+3) & (~3);

	BITMAPFILEHEADER bmp;
	bmp.bfType = 0x4d42;
	bmp.bfSize = 0x36 + (line_numbytes * height);
	bmp.bfReserved1 = 0;
	bmp.bfReserved2 = 0;
	bmp.bfOffBits = 0x36;

	BITMAPINFOHEADER bih;
	bih.biSize          = sizeof(BITMAPINFOHEADER);
	bih.biWidth         = width;
	bih.biHeight        = height;
	bih.biPlanes        = 1;
	bih.biBitCount      = 24;
	bih.biCompression   = BI_RGB;
	bih.biSizeImage     = 0;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed       = 0;
	bih.biClrImportant  = 0;
	
	rgb = fopen(rgb_file, "wb");
	if (!rgb)
		{
		printf("Couldnt create texture file %s\n", rgb_file);
		return;
		}

	#define writeelm(x) fwrite(&(x),sizeof(x),1,rgb)
    writeelm(bmp.bfType);
    writeelm(bmp.bfSize);
    writeelm(bmp.bfReserved1);
    writeelm(bmp.bfReserved2);
    writeelm(bmp.bfOffBits);

    writeelm(bih.biSize);
    writeelm(bih.biWidth);
    writeelm(bih.biHeight);
    writeelm(bih.biPlanes);
    writeelm(bih.biBitCount);
    writeelm(bih.biCompression);
    writeelm(bih.biSizeImage);
    writeelm(bih.biXPelsPerMeter);
    writeelm(bih.biYPelsPerMeter);
    writeelm(bih.biClrUsed);
    writeelm(bih.biClrImportant);

	struct color24
		{
		char r,g,b;
		};

	struct color32
		{
		char r,g,b,a;
		};


	if (bpp == 3)
		{
		for (int i = height-1; i>= 0; i--)
			{
			for (int v = 0; v< width; v++)
				{
				color24 * c = (color24*)(mem+(i*width + v)*sizeof(color24));
				fputc(c->b, rgb);
				fputc(c->g, rgb);
				fputc(c->r, rgb);
				}
			for (int v = 0; v < (line_numbytes - width*3); v++) fputc(0,rgb);
			}
		}

	if (bpp == 4)
		{
		for (int i = height-1; i>= 0; i--)
			{
			for (int v = 0; v< width; v++)
				{
				color32 * c = (color32*)(mem+(i*width+v)*sizeof(color32));
				fputc(c->b, rgb);
				fputc(c->g, rgb);
				fputc(c->r, rgb);
				}
			for (int v = 0; v < (line_numbytes - width*4); v++) fputc(0,rgb);
			}
		}

	fclose(rgb);
	}

if (alpha_file)
	{
	// save the alpha channel to file

	int line_numbytes = width + (width % 4);

	BITMAPFILEHEADER bmp;
	bmp.bfType = 0x4d42;
	bmp.bfSize = 0x36 + (line_numbytes * height) + (sizeof(RGBQUAD)*256);
	bmp.bfReserved1 = 0;
	bmp.bfReserved2 = 0;
	bmp.bfOffBits = 0x36 + (sizeof(RGBQUAD)*256);;

	BITMAPINFOHEADER bih;
	bih.biSize          = sizeof(BITMAPINFOHEADER);
	bih.biWidth         = width;
	bih.biHeight        = height;
	bih.biPlanes        = 1;
	bih.biBitCount      = 8;
	bih.biCompression   = BI_RGB;
	bih.biSizeImage     = 0;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed       = 0;
	bih.biClrImportant  = 0;

	alpha = fopen(alpha_file, "wb");
	if (!alpha)
		{
		printf("Couldnt create texture file %s\n", alpha_file);
		return;
		}

	#undef  writeelm
	#define writeelm(x) fwrite(&(x),sizeof(x),1,alpha)
    writeelm(bmp.bfType);
    writeelm(bmp.bfSize);
    writeelm(bmp.bfReserved1);
    writeelm(bmp.bfReserved2);
    writeelm(bmp.bfOffBits);

    writeelm(bih.biSize);
    writeelm(bih.biWidth);
    writeelm(bih.biHeight);
    writeelm(bih.biPlanes);
    writeelm(bih.biBitCount);
    writeelm(bih.biCompression);
    writeelm(bih.biSizeImage);
    writeelm(bih.biXPelsPerMeter);
    writeelm(bih.biYPelsPerMeter);
    writeelm(bih.biClrUsed);
    writeelm(bih.biClrImportant);

	// save color table
	for (int i=0; i < 256; i++)
		{
		RGBQUAD c;
		c.rgbBlue = i;
		c.rgbGreen = i;
		c.rgbRed = i;
		c.rgbReserved = 0;
		fputc(c.rgbBlue, alpha);
		fputc(c.rgbGreen, alpha);
		fputc(c.rgbRed, alpha);
		fputc(c.rgbReserved, alpha);
		}


	struct color24
		{
		char r,g,b;
		};

	struct color32
		{
		char r,g,b,a;
		};


	if (bpp == 3)
		{
		for (int i = 0; i< height; i++)
			{
			for (int v = 0; v< width; v++)
				{
				color24 * c = (color24*)(mem+(i*width+v)*sizeof(color24));				
				float float_alpha =0;

				float_alpha+=c->r;
				float_alpha+=c->g;
				float_alpha+=c->b;

				float_alpha /= 3;
				
				char byte_alpha = (char)float_alpha;

				//fputc(byte_alpha, alpha);
				fputc(0xff, alpha);
				}
			for (int v = 0; v < (line_numbytes - width); v++) fputc(0,alpha);
			}
		}

	if (bpp == 4)
		{
		for (int i = height-1; i>= 0; i--)
			{
			for (int v = 0; v< width; v++)
				{
				color32 * c = (color32*)(mem+(i*width+v)*sizeof(color32));
				fputc(c->a, alpha);
				}
			for (int v = 0; v < (line_numbytes - width); v++) fputc(0,alpha);
			}
		}

	fclose(alpha);
	}


}