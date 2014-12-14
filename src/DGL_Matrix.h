/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Matrix.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/


#ifndef ___DGL_MATRIX_H
#define ___DGL_MATRIX_H


namespace DGL {
	
	class Matrix {
		public:
			/////////////////////
			// Data
			float matrix[16];


			///////////////////////
			// Constructors creates an identity matrix by default
			inline Matrix()	
			{
				for(unsigned int c=0;c<4;c++)
					for(unsigned int r=0;r<4;r++)
						if(c==r)
							this->matrix[r+c*4]=1.0;
						else
							this->matrix[r+c*4]=0.0;
			}
			inline Matrix(const Matrix& mat)
			{
				this->Set(mat.matrix);
			}
			inline Matrix(const float *mat)
			{
				Set(mat);
			}

			//////////////////////
			// operator =
			inline Matrix& operator = (const Matrix& mat)
			{
				this->Set((float *)&mat);
				return *this;
			}

			//////////////////////
			// Set
			inline void Set(const float *mat)
			{
				for(unsigned int i=0;i<16;i++)
					this->matrix[i]=mat[i];
			}

			//////////////////////
			// Multiply to opengl current matrix
			inline void MultGL() const
			{
				glMultMatrixf(this->matrix);
			}
	};

}// namespace DGL

#endif // ___DGL_MATRIX_H