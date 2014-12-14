/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DMath_Utl.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DMATH_MAIN_H
#define ___DMATH_MAIN_H


namespace DMath 
{

	static const float Pi = 3.14159265358979323846f;
	
	inline float DegToRad( float &a );
	inline float RadToDeg( float &a );

	/*------------------
		Clamp
	------------------*/

	template <class Type> inline static Type Clamp ( Type min, Type max, Type &val);

	/*------------------
		Min
	------------------*/

	template <class Type> inline static Type Min ( Type a, Type b );

	/*------------------
		Max
	------------------*/

	template <class Type> inline static Type Max ( Type a, Type b );

	/*------------------
		Interpolate
	------------------*/

	template <class Type> inline static Type Interpolate ( Type, Type, float);
	template <class Type> inline static Type Interpolate2( Type, Type, Type, float);
	template <class Type> inline static Type Interpolate3( Type, Type, Type, Type, float);

	/*------------------
		Swap
	------------------*/

	template <class Type> inline static void Swap (Type v1,Type v2);

	/*------------------
		Abs
	------------------*/

	template <class Type> inline static Type Abs( Type v );

	/*--------------------
		IsPowerOfTwo
	--------------------*/

	inline static bool IsPowerOfTwo( int v);

	/*-----------------------
		ClosestPowerOfTwo
	-----------------------*/

	inline static int ClosestPowerOfTwo(int v);

} // namespace DMath

#endif // ___DMATH_MAIN_H