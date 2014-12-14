//---------------------------------------------------------------------------
#ifndef fxVectorH
#define fxVectorH
//---------------------------------------------------------------------------

typedef float fxVectorData[3];

class fxVector
	{
	protected:

	public:
		fxVectorData data;

		fxVector();
		fxVector(fxVectorData Data);
		fxVector(float X, float Y, float Z);

		fxVector * Clone(void);
                void Copy(fxVector * vector);

		void Set(float X, float Y, float Z);
		float * Get(void);
		float GetX(void);
		float GetY(void);
		float GetZ(void);

		// memberwise addition
		void Add(float X, float Y, float Z);
		void Add(fxVectorData Data);
		void Add(fxVector * vector);

		// memberwise subtraction
		void Sub(float X, float Y, float Z);
		void Sub(fxVectorData Data);
		void Sub(fxVector * vector);

		// memberwise multiplication
		void Mul(float X, float Y, float Z);
		void Mul(fxVectorData Data);
		void Mul(fxVector * vector);

		// memberwise division
		void Div(float X, float Y, float Z);
		void Div(fxVectorData Data);
		void Div(fxVector * vector);

		// scalar multiplication
		void MulS(float scalar);

		// scalar division
		void DivS(float scalar);

		// return dot product with given vector
		float DotProduct(float X, float Y, float Z);
		float DotProduct(fxVectorData Data);
		float DotProduct(fxVector * vector);

		// return cross product with given vector (cross product returns a vector
		// perpendicular to the two vectors)
		fxVector * CrossProduct(float X, float Y, float Z);
		fxVector * CrossProduct(fxVectorData Data);
		fxVector * CrossProduct(fxVector * vector);

		// length of vector
		float Length(void);

		// square length
		float SquareLength(void);

		// normalize vector (make length == 1) and return former length
		float Normalize(void);

		// memberwise negation (switch signs)
		void Invert(void);

		// return distance to vector
		float Distance(float X, float Y, float Z);
		float Distance(fxVectorData Data);
		float Distance(fxVector * vector);

		// transform vector by matrix
//		void Transform(fxMatrix * matrix);
	};

#endif
