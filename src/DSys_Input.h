/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_Input.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DSYS_INPUT_H
#define ___DSYS_TIMER_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


namespace DSys {

	class Input {
		public:
			enum {
				KEY_RELESED,
				KEY_HELD,
				DIM_MAX	= 4
			};
	
		private:
			static bool					ready;				// Ready?
			static unsigned char		keyBuffer[256];		// The keyboard's key buffer
			static unsigned char		keyCharBuffer[256];	// Key char processed?
			static DIMOUSESTATE			mouseState;			// The mouse's 'buffer'
			static unsigned char		mouseCharBuffer[4];	// Mouse char processed?
			static LPDIRECTINPUT8		lpdi;				// Main DirectInput object
			static LPDIRECTINPUTDEVICE8	lpdiKeyboard;		// Keyboard's DirectInput device
			static LPDIRECTINPUTDEVICE8	lpdiMouse;			// Mouse's DirectInput device
	
			static void GetWheelMovement();
			static void GetMouseMovement();
			
			static int					x;					// Mouse positions
			static int					y;
			static int					z;					// For wheel movement
		public:
			
	
			static void Init(HWND,HINSTANCE);
			static void Shutdown();
			static void Update();
	
			static bool KeyDown(unsigned char key);
			static int KeyValue(unsigned char key);
			static bool KeyChar(unsigned char key);
			static bool MouseDown(unsigned char button);
			static bool MouseChar(unsigned char button);
			static int	MouseXDelta();
			static int	MouseYDelta();
			static int	MouseZDelta();
	};

}

#endif // ___DSYS_TIMER_H