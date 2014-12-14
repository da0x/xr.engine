/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.2 $
	$Date: 2003/10/27 04:00:31 $
	$Id: DE_TD_Shared.h,v 1.2 2003/10/27 04:00:31 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/

#ifndef ___DE_TD_SHARED_H
#define ___DE_TD_SHARED_H

namespace TD
	{
	namespace shared
		{
		class entity
			{
			public: entity( std::string _Classname);
					entity( const entity& _Copy);
					entity& operator = ( const entity& _Right);

			protected: std::string		classname;

					   float			radius;
					   Vector			position;
					   Vector			direction;
					   Vector			velocity;

					   bool				linked;
			};

		namespace event
			{
			
			class basic_event
				{
				public: basic_event( std::string _Classname);
						virtual bool check() = 0;
						virtual void fire() = 0;

				private: std::string		classname;
				};

			class time: public basic_event
				{
				public: time( std::string _Classname, float _TimeTrigger);
						virtual bool check();
						virtual void fire();

				protected: float timeTrigger;
						   bool fired;
				};
											
			class keydown: public basic_event
				{
				public: keydown( std::string _Classname, unsigned char  _Key);
						virtual bool check();

				protected: unsigned char key;
				};

			class keychar: public basic_event
				{
				public: keychar( std::string _Classname, unsigned char  _Key);
						virtual bool check();

				protected: unsigned char key;
				};
			}// event
		}// shared
	}// TD


#endif // ___DE_TD_H