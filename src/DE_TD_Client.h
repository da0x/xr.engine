/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.1 $
	$Date: 2004/09/12 04:21:44 $
	$Id: DE_TD_Client.h,v 1.1 2004/09/12 04:21:44 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DE_TD_CLIENT_H
#define ___DE_TD_CLIENT_H

namespace TD
	{
	namespace client
		{
		class entity: public shared::entity
			{
			private: entity( std::string _Classname ) : shared::entity(_Classname)
						 {
						 }
			};


		}
    }


#endif // ___DE_TD_CLIENT_H