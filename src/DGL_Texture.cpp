/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Texture.cpp,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



/*
TODO List:
- ...
*/

#include "DGL_Main.h"
#include "DGL_Texture.h"
#include "DGL_Extensions.h"


#include <direct.h>
//#include "ijl.h"


#include "OldDGL_Texture.h"

namespace DGL {


	/////////////////////////////////////
	// auxFilter : aux instance
	Texture::Filter		Texture::auxFilter(Filter::FilterName::TRILINEAR);

	/////////////////////////////////////
	// Texture::Filter
	Texture::Filter::Filter(int filter, bool noRepeat)
	{
		switch(filter)
		{
			case NEAREST:
				this->textureGenMipmap = false;
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;
			case LINEAR:
				this->textureGenMipmap = false;
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;
			case BILINEAR:
				this->textureGenMipmap = true;
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				break;
			case TRILINEAR:
				this->textureGenMipmap = true;
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				this->SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				break;
		}

		if(!noRepeat)
		{
			this->textureWarpS			= GL_REPEAT;
			this->textureWarpT			= GL_REPEAT;
		}
		else
		{
			if(Extensions::IsEnabled_GL_EXT_texture_edge_clamp())
			{
				this->textureWarpS			= GL_CLAMP_TO_EDGE;
				this->textureWarpT			= GL_CLAMP_TO_EDGE;
			}
			else if (Extensions::IsEnabled_GL_SGIS_texture_edge_clamp())
			{
				this->textureWarpS			= GL_CLAMP_TO_EDGE_SGIS;
				this->textureWarpT			= GL_CLAMP_TO_EDGE_SGIS;
			}
			else
			{
				this->textureWarpS			= GL_CLAMP;
				this->textureWarpT			= GL_CLAMP;
			}
		}
	}




	/////////////////////////////////////
	// Texture::Filter : Copy constructor
	Texture::Filter::Filter(Texture::Filter& other)
	{
		this->textureGenMipmap = other.textureGenMipmap;
		this->textureMagFilter = other.textureMagFilter;
		this->textureMinFilter = other.textureMinFilter;
		this->textureWarpS = other.textureWarpS;
		this->textureWarpT = other.textureWarpT;
	}
	
	/////////////////////////////////////
	// Texture::Filter::SetParameter
	void Texture::Filter::SetParameter( GLenum target, GLenum pname, GLint param)
	{
		if(target != GL_TEXTURE_2D) return;
		switch (pname)
		{
			case GL_TEXTURE_MAG_FILTER:
				this->textureMagFilter = param;
				break;
			case GL_TEXTURE_MIN_FILTER:
				this->textureMinFilter = param;
				break;
			case GL_TEXTURE_WRAP_S:
				this->textureWarpS = param;
				break;
			case GL_TEXTURE_WRAP_T:
				this->textureWarpT = param;
				break;
		}
	}

	/////////////////////////////////////
	// Texture::Filter::GetParameter
	GLint Texture::Filter::GetParameter( GLenum pname)
	{
		switch (pname)
		{
			case GL_TEXTURE_MAG_FILTER:
				return this->textureMagFilter;
			case GL_TEXTURE_MIN_FILTER:
				return this->textureMinFilter;
			case GL_TEXTURE_WRAP_S:
				return this->textureWarpS;
			case GL_TEXTURE_WRAP_T:
				return this->textureWarpT;
		}
		return 0;
	}
	
	/////////////////////////////////////
	// Texture::Filter::Use
	void Texture::Filter::Use() const
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->textureMinFilter);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->textureMagFilter);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->textureWarpS);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->textureWarpT);
	}

	/////////////////////////////////////
	// Texture::Filter::IsMipmap
	bool Texture::Filter::IsMipmap() const
	{
		return this->textureGenMipmap;
	}







	/////////////////////////////////////
	// Texture::Image
	Texture::Image::Image()
		:
			format(0),
			width(0),
			height(0),
			components(0),
			data(NULL)
	{	
	}

	Texture::Image::~Image()
	{
//		delete [] this->data;
	}

	////////////////////////////////////
	// Texture::Image::Free
	void Texture::Image::Free()
	{
		this->format = 0;
		this->width = 0;
		this->height = 0;
		this->components = 0;
		delete [] this->data;
		this->data = NULL;
	}

	////////////////////////////////////
	// Texture::Image::Resize
	void Texture::Image::Resize(float newWidth, float newHeight)
	{
		if(!this->data)
			return;

		if(newHeight <0)
		{
			newHeight = this->height * (newWidth/this->width);
		}

		unsigned char* newData = new unsigned char[ newWidth * newHeight * this->components];
		gluScaleImage (
				this->format,
				this->width,
				this->height,
				GL_UNSIGNED_BYTE,
				this->data,
				newWidth, 
				newHeight, 
				GL_UNSIGNED_BYTE, 
				newData);
		delete [] this->data;
		this->data = newData;
		this->width = newWidth;
		this->height = newHeight;
	}

	////////////////////////////////////
	// Texture::Image::Scale
	void Texture::Image::Scale(float f)
	{
		if(f <= 0)	return;
		this->Resize(this->width * f, this->height * f);
	}




	///////////////////////////////////
	// Texture::ImageBMP::Load
	void Texture::ImageBMP::Load(const char *filename)
	{
		DGL::LogPrint("Loading BMP Image '%s'...",filename);
#if 0
		// check for image file existance to prevent
		// auxDIBImageLoad() from diplaying a message box
		if(!D_FileExist(filename))
			throw Daher::Exception("File Not Found");

		AUX_RGBImageRec *auxImage = auxDIBImageLoad(filename);
		if(auxImage){
			this->format = GL_RGB;
			this->components = 3;
			this->width = auxImage->sizeX;
			this->height = auxImage->sizeY;
			this->data = auxImage->data;
		}
		free(auxImage);
#endif
	}


	////////////////////////////////////
	// Texture::ImageTGA::Load
	void Texture::ImageTGA::Load(const char* filename)
	{
		int				columns, rows, numPixels;
		unsigned char	*pixbuf;
		int				row, column;
		unsigned char	*buf_p;
		unsigned char	*buffer;
		int				length;
		TargaHeader		targaHeader;
		unsigned char	*targa_rgba;
		unsigned char	tmp[2];
		FILE			*fp;

		// output
		int				width;
		int				height;

		DGL::LogPrint("Loading TGA Image '%s'...",filename);
        
		//
		// load the file
		//
		fp = fopen(filename, "rb");
		if(!fp)
			throw Daher::Exception("File Not Found");
		
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		try {
			buffer = new unsigned char[length];
		} catch (std::bad_alloc) {
			throw Daher::Exception("Cannot allocate memory for TGA texture");
		}

		int result = fread(buffer, length, 1, fp);
		fclose(fp);

		buf_p = buffer;
		targaHeader.idLength = *buf_p++;
		targaHeader.colormapType = *buf_p++;
		targaHeader.imageType = *buf_p++;

		tmp[0] = buf_p[0];
		tmp[1] = buf_p[1];
		targaHeader.colormapIndex = MAKEWORD( tmp[0], tmp[1] );
		buf_p+=2;
		tmp[0] = buf_p[0];
		tmp[1] = buf_p[1];
		targaHeader.colormapLength = MAKEWORD( tmp[0], tmp[1] );
		buf_p+=2;
		targaHeader.colormapSize = *buf_p++;
		targaHeader.xOrigin = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.yOrigin = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.width = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.height = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.pixelSize = *buf_p++;
		targaHeader.attributes = *buf_p++;

		if (targaHeader.imageType!=2 
			&& targaHeader.imageType!=10) 
			throw Daher::Exception("Only type 2 and 10 targa RGB images supported");

		if (targaHeader.colormapType !=0 
			|| (targaHeader.pixelSize!=32 && targaHeader.pixelSize!=24))
			throw Daher::Exception("Only 32 or 24 bit images supported (no colormaps)");

		columns = targaHeader.width;
		rows = targaHeader.height;
		numPixels = columns * rows;

		width = columns;
		height = rows;

		this->data = new unsigned char[numPixels*4];
		targa_rgba = this->data;

		if (targaHeader.idLength != 0)
			buf_p += targaHeader.idLength;  // skip TARGA image comment

		if (targaHeader.imageType==2) {  // Uncompressed, RGB images
			for(row=0; row< rows;  row++) {
				pixbuf = targa_rgba + row*columns*4;
				for(column=0; column<columns; column++) {
					unsigned char red,green,blue,alphabyte;
					switch (targaHeader.pixelSize) {
						case 24:
                            blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = 255;
							break;
						case 32:
							blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							alphabyte = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = alphabyte;
							break;
					}
				}
			}
		}
		else if (targaHeader.imageType==10) {   // Runlength encoded RGB images (RLE)
			unsigned char red,green,blue,alphabyte,packetHeader,packetSize,j;
			for(row=0; row<rows; row++) {
				pixbuf = targa_rgba + row*columns*4;
				for(column=0; column<columns; ) {
					packetHeader= *buf_p++;
					packetSize = 1 + (packetHeader & 0x7f);
					if (packetHeader & 0x80) {        // run-length packet
						switch (targaHeader.pixelSize) {
							case 24:
								blue = *buf_p++;
								green = *buf_p++;
								red = *buf_p++;
								alphabyte = 255;
								break;
							case 32:
								blue = *buf_p++;
								green = *buf_p++;
								red = *buf_p++;
								alphabyte = *buf_p++;
								break;
						}
						for(j=0;j<packetSize;j++) {
							*pixbuf++=red;
							*pixbuf++=green;
							*pixbuf++=blue;
							*pixbuf++=alphabyte;
							column++;
							if (column==columns) { // run spans across rows
								column=0;
								if (row<rows)
									row++;
								else
									goto breakOut;
								pixbuf = targa_rgba + row*columns*4;
							}
						}
					} else {                            // non run-length packet
						for(j=0;j<packetSize;j++) {
							switch (targaHeader.pixelSize) {
								case 24:
									blue = *buf_p++;
									green = *buf_p++;
									red = *buf_p++;
									*pixbuf++ = red;
									*pixbuf++ = green;
									*pixbuf++ = blue;
									*pixbuf++ = 255;
									break;
								case 32:
									blue = *buf_p++;
									green = *buf_p++;
									red = *buf_p++;
									alphabyte = *buf_p++;
									*pixbuf++ = red;
									*pixbuf++ = green;
									*pixbuf++ = blue;
									*pixbuf++ = alphabyte;
									break;
							}
							column++;
							if (column==columns) { // pixel packet run spans across rows
								column=0;
								if (row<rows)
									row++;
								else
									goto breakOut;
								pixbuf = targa_rgba + row*columns*4;
							}						
						}
					}
				}
breakOut:;
			}
		}
		delete [] buffer;

		this->components	= 4;
		this->width			= width;
		this->height		= height;
		this->format		= GL_RGBA;
	}



	/////////////////////////////////////////
	// Texture::ImageJPG::Load
	void Texture::ImageJPG::Load(const char *filename)
	{
	throw Daher::Exception("Cannot load image: IJL initialization failed");
#if 0
		JPEG_CORE_PROPERTIES		image;
		unsigned char				*imageBits = NULL;		// the bits, before swapping
		int							imageSize = 0;
		
		DGL::LogPrint("Loading JPEG Image '%s' ...",filename);
		ZeroMemory( &image, sizeof( JPEG_CORE_PROPERTIES ) );
		// try to init the image 'container'
		if( ijlInit( &image ) != IJL_OK )
			throw Daher::Exception("Cannot load image: IJL initialization failed");

		image.JPGFile = const_cast<char*>(filename);
		// try to read the params from the file
		if( ijlRead( &image, IJL_JFILE_READPARAMS ) != IJL_OK )
			throw Daher::Exception("File Not Found");

		// check info about the channels
		switch(image.JPGChannels) {
			case 1:
				image.JPGColor = IJL_G;
				break;
			case 3:
				image.JPGColor = IJL_YCBCR;
				break;
			default:
				// This catches everything else, but no
				// color twist will be performed by the IJL.
				image.DIBColor = (IJL_COLOR)IJL_OTHER;
				image.JPGColor = (IJL_COLOR)IJL_OTHER;
				break;
		}
		image.DIBWidth    = image.JPGWidth;
		image.DIBHeight   = image.JPGHeight;
		image.DIBChannels = 3;
		image.DIBPadBytes = IJL_DIB_PAD_BYTES(image.DIBWidth,image.DIBChannels);
		imageSize = (image.DIBWidth * image.DIBChannels + image.DIBPadBytes) * image.DIBHeight;
		// allocate memory to store the image unsigned chars (the info OGL wants)
		imageBits = new unsigned char[ imageSize ];
		this->data = new unsigned char[ imageSize ];

		image.DIBBytes = imageBits;
		// Read the image unsigned chars from the image
		if( ijlRead( &image, IJL_JFILE_READWHOLEIMAGE ) != IJL_OK ) {
			delete [] imageBits;
			delete [] this->data;
			this->data = NULL;
			return;
		}
		// free the image container
		if( ijlFree( &image ) != IJL_OK ) 
			throw Daher::Exception("Cannot Free IJL Container");

		this->width	= image.DIBWidth;
		this->height = image.DIBHeight;
		// the JPG stores its image unsigned chars in a different order, instead of
		// going from lower to higher lines it goes higher to lower.
		// Use imageBits2 after this loop.
		for (int j = 0;j < this->height; j++) {
			for (int i = 0;i < this->width; i++) {
				this->data[(j * this->width+i)* 3+ this->Red] = imageBits[((this->height-1-j) * this->width+i)* 3+ this->Blue];
				this->data[(j * this->width+i)* 3+ this->Green] = imageBits[((this->height-1-j) * this->width+i)* 3+ this->Green];
				this->data[(j * this->width+i)* 3+ this->Blue] = imageBits[((this->height-1-j) * this->width+i)* 3+ this->Red];
			}
		}
		// free memory
		delete [] imageBits;
#endif
	}












	
	/* ------------------- */
	/*     BuildTexture    */
	/* ------------------- */
	unsigned int Texture::_buildTexture(
			GLenum					target,
			GLint					components, 
			GLint					width,
			GLint					height,
			GLenum					format,
			GLenum					type, 
			const void				*data,
			const Texture::Filter	filter
	){
		GLuint texture;
		glGenTextures(1, &texture);
		DGL::LogPrint("Texture ID: %d", texture);
		glBindTexture( GL_TEXTURE_2D, texture);

		filter.Use();
		if(filter.IsMipmap())
			gluBuild2DMipmaps (
				target,
				components,
				width,
				height,
				format,
				type,
				data);
		else
			glTexImage2D(
				target,
				0,
				components,
				width,
				height,
				0,
				format,
				type,
				data);
		return texture;
	}

	/*
	==========================
	Build a texture
	==========================
	*/

	void Texture::Build(const char *filename, Texture::Filter filter)
	{
#pragma message( "Texture::Build() is not finished...")
#if 0
		size_t len = strlen(filename);
		const char *s= filename+ len- 3;

		if		(!strcmpi(s, "bmp"))	image = new ImageBMP;
		else if (!strcmpi(s, "tga"))	image = new ImageTGA;
		else if (!strcmpi(s, "jpg"))	image = new ImageJPG;
		else
		{
			DGL::LogError("Can't load image for texture: Unknown Format \"%s\" File\"%s\"",s, filename);
			return;
		}

		try {
			
			image->Load(filename);
            
			
			// First check the size:
			GLint maxSize;
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);

			GLint			width	= image->Width();
			GLint			height	= image->Height();

			if((width > maxSize)||(height > maxSize)||
				!IsPowerOfTwo(height)||!IsPowerOfTwo(width))
			{
				Clamp <GLint> ( 1, maxSize, width);
				Clamp <GLint> ( 1, maxSize, height);
				width = ClosestPowerOfTwo(width);
				height= ClosestPowerOfTwo(height);
				DGL::LogPrint(
					"Texture size is invalid: "
					"Resizing from (%i,%i) to (%i,%i)",
					image->Width(),image->Height(),width,height);

				image->Resize(width,height);
			}
			
			
			this->glTexture = Texture::_buildTexture(
										GL_TEXTURE_2D,
										image->Get(Image::COMPONENTS),
										image->Get(Image::WIDTH),
										image->Get(Image::HEIGHT),
										image->Get(Image::FORMAT),
										GL_UNSIGNED_BYTE,
										image->Data(),
										filter);
			delete image;


		} catch (Daher::Exception& ex) {
			LogError("Error Loading Image: \"%s\"", ex.What() );
		}
#else
		OldDGL::Texture::UseFilter(OldDGL::Texture::FILTER_TRILINEAR);
		OldDGL::Texture::SetParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filter.GetParameter(GL_TEXTURE_WRAP_S) );
		OldDGL::Texture::SetParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filter.GetParameter(GL_TEXTURE_WRAP_T) );

		char s[1024];
		D_strcpy(s, filename);
		this->glTexture = OldDGL::Texture::Load(s);
#endif
	}

	void Texture::Delete()
	{
		if(this->glTexture)
			glDeleteTextures(1, &this->glTexture);
	}

	/*
	================== 
	ScreenShot
	================== 
	*/  
	
	void Texture::_ScreenShot( int width, int height){
		unsigned char	*buffer;
		char			picname[80]; 
		char			checkname[64];
		int				i, c, temp;
		FILE			*f;

		// create the scrnshots directory if it doesn't exist
		sprintf (checkname, "screenshots");
		mkdir (checkname);

		// 
		// find a file name to save it to 
		// 
		strcpy(picname,"shot0000.tga");
		for (i=0; i<=9999 ; i++){
			temp = i;
			for ( c=7; c>=4 ; c--){
				picname[c] = temp%10 + '0';
				temp/=10;
			}
			sprintf (checkname, "screenshots/%s", picname);
			f = fopen (checkname, "rb");
			if (!f)
				break;	// file doesn't exist
			fclose (f);
		}
		if (i==10000){
			DGL::LogError ("Texture::ScreenShot(): Couldn't create a file."); 
			return;
		}
		DGL::LogPrint ("writing screenshots/%s", picname);
		buffer = new unsigned char [width*height*3 + 18];
		if(!buffer){
			DGL::LogError("Couldn't write screenshot. Memory Full");
		}
		memset (buffer, 0, 18);
		buffer[2] = 2;		// uncompressed type
		buffer[12] = width&255;
		buffer[13] = width>>8;
		buffer[14] = height&255;
		buffer[15] = height>>8;
		buffer[16] = 24;	// pixel size
		glReadPixels (0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer+18 ); 
		// swap rgb to bgr
		c = 18+width*height*3;
		for (i=18 ; i<c ; i+=3)	{
			temp = buffer[i];
			buffer[i] = buffer[i+2];
			buffer[i+2] = temp;
		}
		f = fopen (checkname, "wb");
		if(fwrite (buffer, 1, c, f) != width*height*3 + 18)
			DGL::LogError("Couldn't write screenshot. Disk Full");
		fclose (f);
		free (buffer);
	}



}// namespace DGL;