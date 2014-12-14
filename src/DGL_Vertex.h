/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Vertex.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DVERTEX_H
#define ___DVERTEX_H

namespace DGL {

	class Vertex : public Vector {
		public:
			Vertex() { }
			Vertex( const Vertex& v) : Vector(v.x_(), v.y_(), v.z_()) { }
			Vertex( const float x, const float y, const float z): Vector(x,y,z) { }
			Vertex( const float* fv) : Vector(fv) { }

			inline Vertex& operator = (const Vertex& v){
				(*this).Set(v);
				return *this;
			}
			inline Vertex operator + (const Vertex& v) const {
				return Vertex(x+v.x_(),y+v.y_(),z+v.z_());
			}
			inline Vertex operator - (const Vertex& v) const {
				return Vertex(x*v.x_(),y*v.y_(),z*v.z_());
			}
			inline Vertex& operator += (const Vertex& v){
				return *this = *this + v;
			}
			inline Vertex& operator -= (const Vertex& v){
				return *this = *this - v;
			}


			inline void Translate() const {
				glTranslatef(x,y,z);
			}
			inline void Rotate() const {
				glRotatef(1, x,y,z);
			}
			inline void Pop() const {
				glVertex3fv(v);
			}
			inline void Pop2D() const {
				glVertex2fv(v);
			}
	};

}//namespace DGL


#endif // ___DVERTEX_H