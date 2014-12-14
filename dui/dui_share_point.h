/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_share_point.h,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_SHARE_POINT_H
#define __DUI_SHARE_POINT_H

namespace dui
	{
	namespace share
		{
		class point
			{
			private: typedef point			instance;
					 typedef point&			reference;
					 typedef const point&	constant_reference;

			public:	int x;
					int y;

			public: inline instance operator + (constant_reference right) const;
					inline instance operator - (constant_reference right) const;
					inline reference operator = (constant_reference copy);
					inline reference operator += (constant_reference right);
					inline reference operator -= (constant_reference right);
					inline bool operator ==(constant_reference right) const;
					inline bool operator !=(constant_reference right) const;
					inline bool operator > (constant_reference right) const;
					inline bool operator >=(constant_reference right) const;
					inline bool operator < (constant_reference right) const;
					inline bool operator <=(constant_reference right) const;
			
			public: point();
					point(int x,int y);
					point(constant_reference copy);
			};

		//inlined
		inline point::instance point::operator + (point::constant_reference right) const
			{
			return point::instance(this->x + right.x, this->y + right.y);
			}
		inline point::instance point::operator - (point::constant_reference right) const
			{
			return point::instance(this->x - right.x, this->y - right.y);
			}
		inline point::reference point::operator = (point::constant_reference copy)
			{
			this->x = copy.x;
			this->y = copy.y;
			return *this;
			}
		inline point::reference point::operator += (point::constant_reference right)
			{
			this->x += right.x;
			this->y += right.y;
			return *this;
			}
		inline point::reference point::operator -= (point::constant_reference right)
			{
			this->x -= right.x;
			this->y -= right.y;
			return *this;
			}
		inline bool point::operator == (point::constant_reference right) const
			{
			return ( this->x == right.x && this->y == right.y );
			}
		inline bool point::operator != (point::constant_reference right) const
			{
			return ( this->x != right.x && this->y == right.y );
			}
		inline bool point::operator > (point::constant_reference right) const
			{
			return ( this->x > right.x && this->y > right.y );
			}
		inline bool point::operator >=(point::constant_reference right) const
			{
			return ( this->x >= right.x && this->y >= right.y );
			}
		inline bool point::operator < (point::constant_reference right) const
			{
			return ( this->x < right.x && this->y < right.y );
			}
		inline bool point::operator <=(point::constant_reference right) const
			{
			return ( this->x <= right.x && this->y <= right.y );
			}

		// construction
		point::point()
			: x(0),y(0)
			{
			}
		point::point(int x,int y)
			: x(x), y(y)
			{
			}
		point::point(point::constant_reference copy)
			: x(copy.x), y(copy.y)
			{
			}
		}
	}

#endif // __DUI_SHARE_POINT_H