/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:01 $
	$Id: DGL_State.h,v 1.3 2004/07/31 19:22:01 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DGL_STATE_H
#define ___DGL_STATE_H

/* TODO List:
- inhirt from std::stack
- ...
*/

namespace DGL {

	class State {
		public:
			//////////////////////////////////////////////
			// State constructor needs the the stack name
			State(int name) :	stateName(name),
								depth(0)
			{
			}

			/////////////////////////////////////
			// Enable the state
			void Enable()
			{
				glEnable(this->stateName);
			}

			/////////////////////////////////////
			// Disable the state
			void Disable()
			{
				glDisable(this->stateName);
			}

			/////////////////////////////////////
			// Push current value into the stack
			void Push()
			{
				this->stack[this->depth++] = (bool) glIsEnabled(this->stateName);
				if(this->depth >= _STACK_DEPTH )
					throw Daher::Exception("DGL::State::depth exceeded its maximum value");
			}

			////////////////////////////////////
			// Pop current value into the stack
			void Pop()
			{
				if(this->depth-- <= 0)
					throw Daher::Exception("DGL::State::depth is lower than its minimum value");
				if(this->stack[this->depth])
					Disable();
				else
					Enable();
			}


		private:
			int				stateName;
			static const int _STACK_DEPTH = 10;
			bool			stack[_STACK_DEPTH];
			short int		depth;
	};


	/////////////////////////////////////
	// Gloabal instances of opengl states
//	State Lighting(GL_LIGHTING);
//	State Texture2D(GL_TEXTURE_2D);
//	State CullFace(GL_CULL_FACE);
}

#endif // ___DGL_STATE_H