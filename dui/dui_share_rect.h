/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_share_rect.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_SHARE_RECT_H
#define __DUI_SHARE_RECT_H

namespace dui
	{
	namespace share
		{		
		class rect
			{
			public: void set_rect( int x, int y, int w, int h);
					void set_rect( const rect& rect);
					void get_rect( int& x, int& y, int& w, int& h) const;
					void get_rect( rect& rect) const;
					bool point_on_rect( const point& ) const;

			protected: int x;	// x position
					   int y;	// y positoin
					   int w;	// width
					   int h;	// height

			public: rect();
			};
		}
	}


#endif // __DUI_SHARE_RECT_H