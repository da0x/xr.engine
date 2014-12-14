/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:03 $
	$Id: OldDGL_Texture.h,v 1.3 2004/07/31 19:22:03 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___OldDGL_TEXTURE_H
#define ___OldDGL_TEXTURE_H

namespace OldDGL {
	/*
	=============================================================

		TEXTURES

	=============================================================
	*/

	class Texture {
		public:
			enum EFilter{
				FILTER_NEAREST		= 0x0001,
				FILTER_LINEAR		= 0x0002,
				FILTER_BILINEAR		= 0x0003,
				FILTER_TRILINEAR	= 0x0004
			};
		private:
			static bool		textureGenMipmap;
			static EFilter	textureMipMapFilter;
			static int		textureMagFilter;
			static int		textureMinFilter;
			static int		textureWarpS;
			static int		textureWarpT;


			static char			*filterName(EFilter f);
			static void			applyParameters();
			static unsigned int buildTexture(GLenum target, GLint components, GLint width, GLint height, GLenum format, GLenum type, const void  *data);
		
			/* ---------------------- */
			/*   Texture Parameters   */
			/* ---------------------- */
		public:
			static void SetDefaultParameters( void );
			static void SetParameter(GLenum target, GLenum pname, GLint param);

					/*  Supported Parameters and there default values
  						GL_TEXTURE_MAG_FILTER   = GL_LINEAR
						GL_TEXTURE_MIN_FILTER   = GL_LINEAR_MIPMAP_NEAREST
						GL_TEXTURE_WRAP_S       = GL_REPEAT
						GL_TEXTURE_WRAP_T       = GL_REPEAT
					*/

			/* ----------- */
			/*   Filters   */
			/* ----------- */
			
			static void UseFilter(EFilter filter);


			/* ---------------------- */
			/*     Images Loading     */
			/* ---------------------- */

			static unsigned int LoadBMP(char *fname);

			struct TargaHeader {
				unsigned char 	idLength, colormapType, imageType;
				unsigned short	colormapIndex, colormapLength;
				unsigned char	colormapSize;
				unsigned short	xOrigin, yOrigin, width, height;
				unsigned char	pixelSize, attributes;
			};
			static unsigned int LoadTGA(char *fname);
			static unsigned int LoadJPEG(char *fname);

			/*
			-----------------------
			Load Any Texture
			-----------------------
			*/
			static unsigned int Load(char *filename);

			/* -------------- */
			/*  Screen Shots  */
			/* -------------- */
			static void ScreenShot ( int w, int h);
	};
}









namespace OldDGL {
	/* ---------------------- */
	/*   Texture Parameters   */
	/* ---------------------- */
	
	bool				Texture::textureGenMipmap		= false;
	Texture::EFilter	Texture::textureMipMapFilter	= Texture::FILTER_LINEAR;
    int					Texture::textureMagFilter		= GL_LINEAR;
	int					Texture::textureMinFilter		= GL_LINEAR;
	int					Texture::textureWarpS			= GL_REPEAT;
	int					Texture::textureWarpT			= GL_REPEAT;
	
	void Texture::SetDefaultParameters( void ){
		textureMagFilter   = GL_LINEAR;
		textureMinFilter   = GL_LINEAR;
		textureWarpS       = GL_REPEAT;
		textureWarpT       = GL_REPEAT;	
	}

	void Texture::SetParameter( GLenum target, GLenum pname, GLint param){
		if(target != GL_TEXTURE_2D) return;
		switch (pname){
			case GL_TEXTURE_MAG_FILTER:
				textureMagFilter = param;
				break;
			case GL_TEXTURE_MIN_FILTER:
				textureMinFilter = param;
				break;
			case GL_TEXTURE_WRAP_S:
				textureWarpS = param;
				break;
			case GL_TEXTURE_WRAP_T:
				textureWarpT = param;
				break;
		}
	}
	
	
	/* ------------------ */
	/*   Texture Filter   */
	/* ------------------ */
	char *Texture::filterName(EFilter filter){
		switch(filter){
			case FILTER_NEAREST:	return "Nearest";
			case FILTER_LINEAR:		return "Linear";
			case FILTER_BILINEAR:	return "Bilinear";
			case FILTER_TRILINEAR:	return "Trilinear";
			default:				return "UnrecognizedFilter";
		}
	}
	void Texture::UseFilter(EFilter filter){
		DGL::LogPrint("Using %s texture filtering.", filterName(filter));
		textureMipMapFilter = filter;
	}


	/* ---------------------- */
	/*   applyParameters   */
	/* ---------------------- */

	void Texture::applyParameters(){
		switch(textureMipMapFilter){
			case FILTER_NEAREST:
			default:
				textureGenMipmap = false;
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;
			case FILTER_LINEAR:
				textureGenMipmap = false;
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;
			case FILTER_BILINEAR:
				textureGenMipmap = GL_TRUE;
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				break;
			case FILTER_TRILINEAR:
				textureGenMipmap = GL_TRUE;
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				SetParameter( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				break;
		}
	}
	
	/* ------------------- */
	/*     BuildTexture    */
	/* ------------------- */
	unsigned int Texture::buildTexture(
			GLenum      target,
			GLint       components, 
			GLint       width,
			GLint       height,
			GLenum      format,
			GLenum      type, 
			const void  *data
	){
		// First check the size:
		GLint maxSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);

		unsigned char *	_data	= (unsigned char *)data;
		GLint			_width	= width;
		GLint			_height	= height;
		if(	(_width > maxSize)		||
			(_height > maxSize)		||
			!IsPowerOfTwo(_height) ||
			!IsPowerOfTwo(_width)
		){
			Clamp <GLint> ( 1, maxSize, _width);
			Clamp <GLint> ( 1, maxSize, _height);
			_width = ClosestPowerOfTwo(_width);
			_height= ClosestPowerOfTwo(_height);
			_data = new unsigned char [ _width * _height * components ];
			if(!_data){
				DGL::LogError("Not Enough Memory To Build A Texture...");
				return 0;
			}
			gluScaleImage (
				format,
				width,
				height,
				type,
				data,
				_width, 
				_height, 
				type, 
				_data);
			DGL::LogPrint("Texture size is out of range: Resizing from (%i,%i) to (%i,%i)",
				width,height,_width,_height);
		}
		GLuint texture;
		glGenTextures(1, &texture);
		DGL::LogPrint("Texture ID: %d", texture);
		glBindTexture( GL_TEXTURE_2D, texture);
		applyParameters();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,textureMinFilter);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,textureMagFilter);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,textureWarpS);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,textureWarpT);
		if(textureGenMipmap)
			gluBuild2DMipmaps (
				target,
				components,
				_width,
				_height,
				format,
				type,
				_data);
		else
			glTexImage2D(
				target,
				0,
				components,
				_width,
				_height,
				0,
				format,
				type,
				_data);

		delete [] _data;
		return texture;
	}

	/*
	=========================================================
	BMP LOADING
	=========================================================
	*/
	
	unsigned int Texture::LoadBMP(char *filename){
#if 0
		AUX_RGBImageRec *TextureImage;               // Create Storage Space For The Texture
		GLuint texture = 0;
		DGL::LogPrint("Loading BMP texture '%s'...",filename);
		// check for image file existance to prevent
		// auxDIBImageLoad() from diplaying a message box
		FILE *stream = fopen(filename, "rb");
		if(!stream){
			DGL::LogError("File Not Found '%s'",filename);
			return 0;
		} else {
			fclose(stream);
		}
		TextureImage=auxDIBImageLoad(filename);
		if(TextureImage){
			texture =	buildTexture(
				GL_TEXTURE_2D,
				3,
				TextureImage->sizeX,
				TextureImage->sizeY,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				TextureImage->data);
			free(TextureImage->data);
			free(TextureImage);
		}
		return texture;
#endif 
		return 0;
	}
	
	/*
	=========================================================
	TARGA LOADING
	=========================================================
	*/
	/*
	=============
	dglLoadTGA
	=============
	*/
	unsigned int Texture::LoadTGA (char *name){
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
			unsigned char	*pic;

			DGL::LogPrint("Loading TGA Texture '%s'...",name);
            
			//
			// load the file
			//
			fp = fopen(name, "rb");
			if(!fp){
				DGL::LogError("File not found '%s'", name);
				return 0;
			}
			fseek(fp, 0, SEEK_END);
			length = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			buffer = ( unsigned char * ) malloc(length);
			if(!buffer){
				DGL::LogError("Cannot allocate memory for TGA texture '%s'",name);
				return 0;
			}
			fread(buffer, length, 1, fp);
			fclose(fp);
			if (!buffer){
				DGL::LogError ("Bad tga file '%s'", name);
				return 0;
			}
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
				DGL::LogError("Only type 2 and 10 targa RGB images supported");

			if (targaHeader.colormapType !=0 
				|| (targaHeader.pixelSize!=32 && targaHeader.pixelSize!=24))
				DGL::LogError("Only 32 or 24 bit images supported (no colormaps)");

			columns = targaHeader.width;
			rows = targaHeader.height;
			numPixels = columns * rows;

			width = columns;
			height = rows;

			targa_rgba = ( unsigned char * )malloc (numPixels*4);
			pic = targa_rgba;

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
            GLuint texture = buildTexture(
								GL_TEXTURE_2D, 
								4, 
								width,
								height,
								GL_RGBA,
								GL_UNSIGNED_BYTE,
								pic);
			free(buffer);
//			free(pic);

			return texture;
	}
	
	/*
	=========================================================
	JPEG LOADING : using the intel jpeg library.
	=========================================================
	*/

	unsigned int Texture::LoadJPEG(char *filename){
#if 0
		JPEG_CORE_PROPERTIES		image;
		unsigned char				*imageBits = NULL,		// the bits, before swapping
									*imageBits2 = NULL;		// after swapping
		int							imageSize = 0,
									imageWidth = 0,
									imageHeight = 0;
		
		DGL::LogPrint("Loading JPEG Texture '%s' ...",filename);
		ZeroMemory( &image, sizeof( JPEG_CORE_PROPERTIES ) );
		// try to init the image 'container'
		if( ijlInit( &image ) != IJL_OK ) {
			DGL::LogError("cannot load texture: IJL initialization failed");
			return 0;
		}
		image.JPGFile = const_cast<char*>(filename);
		// try to read the params from the file
		if( ijlRead( &image, IJL_JFILE_READPARAMS ) != IJL_OK )  {
			DGL::LogError("File Not Found '%s'",filename);
			return 0;
		}
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
		imageBits2 = new unsigned char[ imageSize ];
		if( (imageBits == NULL) || (imageBits2 == NULL) ) {
			DGL::LogError("Connot allocate memory for JPEG texture '%s'",filename);
			return 0;
		}
		image.DIBBytes = imageBits;
		// Read the image unsigned chars from the image
		if( ijlRead( &image, IJL_JFILE_READWHOLEIMAGE ) != IJL_OK ) {
			delete [] imageBits;
			delete [] imageBits2;
		}
		// free the image container
		if( ijlFree( &image ) != IJL_OK ) {
			DGL::LogError("Cannot Free IJL Container '%s'",filename);
			return 0;			
		}
		imageWidth	= image.DIBWidth;
		imageHeight	= image.DIBHeight;
		// the JPG stores its image unsigned chars in a different order, instead of
		// going from lower to higher lines it goes higher to lower.
		// Use imageBits2 after this loop.
		for (int j = 0;j < imageHeight; j++) {
			for (int i = 0;i < imageWidth; i++) {
				imageBits2[(j * imageWidth+i)* 3] = imageBits[((imageHeight-1-j) * imageWidth+i)* 3+2];
				imageBits2[(j * imageWidth+i)* 3+1] = imageBits[((imageHeight-1-j) * imageWidth+i)* 3+1];
				imageBits2[(j * imageWidth+i)* 3+2] = imageBits[((imageHeight-1-j) * imageWidth+i)* 3];
			}
		}
		// OpenGL part: generate ids, bind texture and create texture
		GLuint texture =	buildTexture(
								GL_TEXTURE_2D,
								3,
								imageWidth,
								imageHeight,
								GL_RGB,
								GL_UNSIGNED_BYTE,
								imageBits2);
		// free memory
		delete [] imageBits;
//		delete [] imageBits2;
		return texture;
#endif
		return 0;
	}



	/*
	==========================
	Load Any Texture
	==========================
	*/

	unsigned int Texture::Load(char *filename){
		char	*s;
		size_t len;
		len = strlen(filename);
		s= filename+ len- 3;
		if (!strcmpi(s, "bmp"))	return Texture::LoadBMP(filename);else
		if (!strcmpi(s, "tga"))	return Texture::LoadTGA(filename);else
		if (!strcmpi(s, "jpg"))	return Texture::LoadJPEG(filename);else
		{
			DGL::LogError("Can't load image for texture: Unknown Format \"%s\" File\"%s\"",s, filename);
			return 0;
		}
	}

	/* 
	============================================================================== 
	SCREEN SHOTS 
	============================================================================== 
	*/ 
	
	/*
	================== 
	ScreenShot
	================== 
	*/  
	
	void Texture::ScreenShot( int width, int height){
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



}// namespace OldDGL;

#endif // ___OldDGL_FRUSTUM_H
