/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DMath_Random.inl,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



	inline void Random::Randomize()
	{
		Random::Seed (time(NULL));
	}

	inline void Random::Seed (unsigned int seed)
	{
		Random::holdrand = seed;
	}

	inline int Random::Int ( void )
	{
		return (((Random::holdrand = Random::holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
	}
	
	inline float Random::Float ()
	{
		return (float)Random::Int() / (float)0x7fff;
	}
