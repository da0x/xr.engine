/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_Material.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___MATERIAL_H
#define ___MATERIAL_H


// Undone!



namespace DGL {

	class Material {
		public:
			Material() :	emission(0.0f, 0.0f, 0.0f, 1.0f),
							ambient(0.2f, 0.2f, 0.2f, 1.0f),
							diffuse(0.8f, 0.8f, 0.8f, 1.0f),
							specular(0.0f, 0.0f, 0.0f, 1.0f),
							shininess(0.0f),
							face(GL_FRONT)
			{
			}
			Material(Material &mat) :	emission(mat.emission),
										ambient(mat.ambient),
										diffuse(mat.diffuse),
										specular(mat.specular),
										shininess(mat.shininess),
										face(mat.face)
			{
			}
			Material(
					Color Emission,
					Color Ambient,
					Color Diffuse,
					Color Specular,
					float Shininess,
					bool doubleFace) :	emission(Emission),
										ambient(Ambient),
										diffuse(Diffuse),
										specular(Specualr),
										shininess(Shininess),
										face(doubleFace ? GL_FRONT_AND_BACK : GL_FRONT)
			{
			}
			Material& operator = (Material& other)
			{
				this->emission = other.emission;
				this->ambient = other.ambient;
				this->diffuse = other.diffuse;
				this->specular = other.specular;
				this->shininess = other.shininess;
				this->face = other.face;
				return *this;
			}

			// sets up opengl to this material properties
			void Setup() const
			{
				glMaterialfv(this->face, GL_EMISSION, this->emission);
				glMaterialfv(this->face, GL_AMBIENT, this->ambient);
				glMaterialfv(this->face, GL_DIFFUSE, this->diffuse);
				glMaterialfv(this->face, GL_SPECULAR, this->specular);
				glMaterialf(this->face, GL_SHININESS, this->shininess );
			}

			// resets opengl material state
			static void _Reset()
			{
				// default values taken from the red book
				glMaterialfv(GL_FRONT, GL_AMBIENT, Color(0.2f, 0.2f, 0.2f, 1.0f));
				glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(0.8f, 0.8f, 0.8f, 1.0f));
				glMaterialfv(GL_FRONT, GL_SPECULAR, Color(0.0f, 0.0f, 0.0f, 1.0f));
				glMaterialf(GL_FRONT, GL_SHININESS, float(0) );
			}

			enum Param {
				EMISSION,
				AMBIENT,
				DIFFUSE,
				AMBIENT_AND_DIFFUSE,
				SPECULAR,
				SHININESS
			};

			void Set(Param param, const Color& c)
			{
				switch (param)
				{
					case SHININESS:
						this->emission = c;
						break;
					case AMBIENT:
						this->ambient = c;
						break;
					case DIFFUSE:
						this->diffuse = c;
						break;
					case AMBIENT_AND_DIFFUSE:
						this->ambient = c;
						this->diffuse = c;
						break;
					case SPECULAR:
						this->specular = c;
						break;
				}
			}

			void Set(Param param, float f)
			{
				switch (param)
				{
					case SHININESS:
						this->shininess = f;
						break;
				}
			}

			enum HintParam {
				SINGLE_FACE,
				DOUBLE_FACE
			};

			void Hint(HintParam hint)
			{
				switch (hint)
				{
					case SINGLE_FACE:
						face = GL_FRONT;
						break;
					case DOUBLE_FACE:
						face = GL_FRONT_AND_BACK:
						break;
				}
			}

		private:
			Color	emission;
			Color	ambient;
			Color	diffuse;
			Color	specular;
			float	shininess;
			GLenum	face;
	};

}//namespace DGL


#endif // ___MATERIAL_H