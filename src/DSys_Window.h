/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Window.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DSYS_WINDOW_H
#define ___DSYS_WINDOW_H

namespace DSys {

	class Window {
		public:
			struct Info {
				const char *title;
				int			width;
				int			height;
				bool		fullscreen;

				int			colorBits;
				int			alphaBits;
				int			depthBits;
				int			stencilBits;
				int			accumBits;
				int			auxBuffers;
			};

			static bool Create( Info* );
			static void Destroy( void);
			static bool ChangeRes(int width, int height, int bits);
			static bool ChangeSize(int width, int height);
			static void SetTitle( const char *);	// Changes The Text On The Title Bar
			static void SwapGLBuffers();			// Swaps the gl buffers

			static HDC	GetDC(){return hDC;}
			static HWND GetHWND(){return hWnd;}
			static bool Active(){return active;}
			static int	Width(){return width;}
			static int	Height(){return height;}
			
		private:
			static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
			static bool				active;			// Active?
			static bool				isFullscreen;	// Are we in fullscreen mode?

			static HDC				hDC;			// Device Context
			static HGLRC			hRC;			// GL Rendering Context
			static HWND				hWnd;			// Window Handle
			static HINSTANCE		hInstance;		// Instance Handle

			static int				width;
			static int				height;
		
	};


}

#endif // ___DSYS_WINDOW_H