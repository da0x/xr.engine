/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:00 $
	$Id: DGL_Frustum.h,v 1.3 2004/07/31 19:22:00 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DGL_FRUSTUM_H
#define ___DGL_FRUSTUM_H

namespace DGL {
	/*
	================================================================

	FRUSTUM

	================================================================
	*/

	class Frustum {
			float frustum[6][4];		// view frustum matrix
		public:
			void	Extract();
			bool	PointInFrustum( const Vector &v ) const ;
			bool	SphereInFrustum( const Vector &v, float radius ) const ;
			float	SphereInFrustumLOD( const Vector &v, float radius ) const ;
			bool	CubeInFrustum( const Vector &v, float size ) const ;
	};

}

#endif // ___DGL_FRUSTUM_H