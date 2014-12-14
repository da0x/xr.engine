/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_share_rect.cpp,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#include "dui.h"

using namespace dui;
using namespace dui::share;

void rect::set_rect( int x, int y, int w, int h)
	{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	}

void rect::set_rect( const rect& rect)
	{
	this->set_rect( rect.x, rect.y, rect.w, rect.h);
	}

void rect::get_rect( int& x, int& y, int& w, int& h) const
	{
	x = this->x;
	y = this->y;
	w = this->w;
	h = this->h;
	}

void rect::get_rect( rect& rect) const
	{
	this->get_rect( rect.x, rect.y, rect.w, rect.h);
	}

bool rect::point_on_rect( const point& pnt ) const
	{
	const point lower_left(x,y);
	const point upper_right(x+w,y+h);
	return pnt > lower_left && pnt < upper_right;
	}

rect::rect()
	: x(0), y(0), w(0), h(0)
	{
	}