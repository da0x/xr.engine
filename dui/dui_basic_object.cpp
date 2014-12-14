/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui_basic_object.cpp,v 1.3 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#include "dui.h"

using namespace dui;
using namespace dui::basic;

object::object()
	{
	this->visible = false;
	this->enabled = false;
	}

void object::show()
	{
	this->visible = true;
	}

void object::hide()
	{
	this->visible = false;
	}

bool object::is_visible()
	{
	return this->visible;
	}

void object::enable()
	{
	this->enabled = true;
	}

void object::disable()
	{
	this->enabled = false;
	}

bool object::is_enabled()
	{
	return this->enabled;
	}

void object::on_click( const share::point& )
	{ // do nothing
	}

void object::on_mouse_move( const share::point& )
	{ // do nothing
	}

void object::on_mouse_down( const share::point& )
	{ // do nothing
	}

void object::on_mouse_up()
	{ // do nothing
	}

void object::on_key_down()
	{ // do nothing
	}

void object::on_key_up()
	{ // do nothing
	}

