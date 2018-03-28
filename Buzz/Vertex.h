#ifndef VERTEX_H
#define VERTEX_H


#include <GL\glew.h>

namespace BUZZ
{
	struct Position
	{
		GLfloat x;
		GLfloat y;

		void set(GLfloat x_, GLfloat y_)
		{
			x = x_;
			y = y_;
		}
	};

	struct UV
	{
		GLfloat u;
		GLfloat v;

		void set(GLfloat u_, GLfloat v_)
		{
			u = u_;
			v = v_;
		}
	};

	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		void set(GLubyte r_, GLubyte g_, GLubyte b_, GLubyte a_)
		{
			r = r_;
			g = g_;
			b = b_;
			a = a_;
		}
	};

	struct Vertex
	{
		Position position;
		UV uv;
	};

	struct DebugVertex
	{
		Position position;
		Color color;
	};
}


#endif // VERTEX_H