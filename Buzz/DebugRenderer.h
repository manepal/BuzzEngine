#ifndef DEBUG_RENDERER
#define DEBUG_RENDERER

#include <GL\glew.h>
#include <Box2D\Box2D.h>

#include "ShaderProgram.h"

namespace BUZZ
{
	class DebugRenderer : public b2Draw
	{
	public:
	/*	DebugRenderer();
		~DebugRenderer();

		void init();*/

		// Inherited via b2Draw
		virtual void DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color) override;
		virtual void DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color) override;
		virtual void DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color) override;
		virtual void DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color) override;
		virtual void DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color) override;
		virtual void DrawTransform(const b2Transform & xf) override;
		virtual void DrawPoint(const b2Vec2 & p, float32 size, const b2Color & color) override;

	//private:
//		ShaderProgram m_shaderProgram;
///*
//		static const GLchar* m_vertSource;
//		static const GLchar* m_fragSource;*/
//
//		GLuint m_vbo;
//		GLuint m_ibo;
//		GLuint m_vao;
	};
}


#endif // !DEBUG_RENDERER