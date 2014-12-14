/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Tomas_m3ds.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef M3DS_H_INCLUDED
#define M3DS_H_INCLUDED

#include "DGL_Tomas_Model.h" // base class

namespace DGL {
	namespace Tomas {

		class M3ds : public Model {
				void Load(std::istream &instream);
				void ReadChunks(std::istream &instream,int chunklength);
			public:
				M3ds(const char *filename);
				M3ds(std::istream &instream);
		};

	} // namespace Tomas
}// namespace DGL

#endif
