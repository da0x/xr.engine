/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.4 $
	$Date: 2004/09/11 05:18:51 $
	$Id: DGL_ModelMilkshape.h,v 1.4 2004/09/11 05:18:51 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DGL_MODELMILKSHAPE_H
#define ___DGL_MODELMILKSHAPE_H

/*
TODO List:
- ...
*/


namespace DGL {

	// Declerations of base class
	class Model;


	class ModelMilkshape : public Model
	{
		public:
			/*	Constructor. */
			ModelMilkshape();

			/*	Destructor. */
			virtual ~ModelMilkshape();

			/*	
				Load the model data into the private variables. 
					filename			Model filename
			*/
			virtual bool LoadModelData( std::string filename );
	};
}//namespace DGL
#endif // ___DGL_MODELMILKSHAPE_H