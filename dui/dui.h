/*
-------------------------------------------
DUI - Daher Engine's User Interface Library
-------------------------------------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/07/31 19:21:59 $
	$Id: dui.h,v 1.4 2004/07/31 19:21:59 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef __DUI_H
#define __DUI_H


#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>

#pragma warning( disable : 4584 )  // base-class 'base' is already a base-class of 'derived'
#define __dui

#include "../src/dsys.h"
#include "../src/dgl.h" // using "../src/dgl_shader.h"

namespace dui
	{
	using std::vector;
	using std::string;
	using std::list;

	typedef class DGL::Shader       shader;
	typedef class DGL::ShaderLib    shader_library;

	class __dui server;
	}

#include "dui_const.h"
#include "dui_share.h"
#include "dui_basic.h"

#include "dui_graphics.h"
#include "dui_control.h"
#include "dui_menu.h"
#include "dui_system.h"

#include "dui_server.h"



#endif // __DUI_H