#include "DebugRenderer.h"

#define GLSL(version, shader)  "#version " #version "\n" #shader

namespace BUZZ
{
	/*const GLchar* m_vertSource = GLSL(330,
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec4 color;
		
		vout vec4 fragColor;

		uniform mat4 model;

		void main
		{
			gl_Position = vec4(position, 0.0f, 1.0f);

			fragColor = color;
		}
	);

	const GLchar* m_fragSource = GLSL(330,
		in vec4 fragColor;

		out vec4 outColor;

		void main()
		{
			outColor = fragColor;
		}
	);*/
/*
	DebugRenderer::DebugRenderer():
		m_vbo(0),
		m_ibo(0),
		m_vao(0)
	{
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		glGenVertexArrays(1, &m_vao);
	}


	DebugRenderer::~DebugRenderer()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void BUZZ::DebugRenderer::init()
	{
	}
*/
	void BUZZ::DebugRenderer::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
	{
		glColor4f(color.r, color.g, color.b, 0.5f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < vertexCount; i++)
		{
			b2Vec2 v = vertices[i];
			glVertex2f(v.x * 30, v.y * 30);
		}
		glEnd();

		//glBindVertexArray(m_vao);

		//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//// position attribute
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(b2Vec2) + sizeof(b2Color), nullptr);
		//glEnableVertexAttribArray(0);

		//// color attribute
		//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(b2Vec2) + sizeof(b2Color), (GLvoid*)(sizeof(b2Vec2)));
		//glEnableVertexAttribArray(1);

		//glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	}

	void BUZZ::DebugRenderer::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
	{
		glColor4f(color.r, color.g, color.b, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < vertexCount; i++)
		{
			b2Vec2 v = vertices[i];
			glVertex2f(v.x * 30, v.y * 30);
		}
		glEnd();

		//glBindVertexArray(m_vao);

		//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//// position attribute
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(b2Vec2) + sizeof(b2Color), nullptr);
		//glEnableVertexAttribArray(0);

		//// color attribute
		//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(b2Vec2) + sizeof(b2Color), (GLvoid*)(sizeof(b2Vec2)));
		//glEnableVertexAttribArray(1);

		//glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	}

	void BUZZ::DebugRenderer::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
	{
		const float32 k_segments = 16.0f;
		const int vertexCount = 16;
		const float32 k_increment = 2.0f * b2_pi / k_segments;
		float32 theta = 0.0f;

		glColor4f(color.r, color.g, color.b, 1);
		glBegin(GL_LINE_LOOP);
		GLfloat glVertices[vertexCount * 2];
		for (int32 i = 0; i < k_segments; ++i)
		{
			b2Vec2 v = center + radius * b2Vec2(cos(theta), sin(theta));
			glVertex2f(v.x * 30, v.y * 30);
			theta += k_increment;
		}
		glEnd();
	}

	void BUZZ::DebugRenderer::DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color)
	{
		const float32 k_segments = 16.0f;
		const int vertexCount = 16;
		const float32 k_increment = 2.0f * b2_pi / k_segments;
		float32 theta = 0.0f;

		glColor4f(color.r, color.g, color.b, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		GLfloat glVertices[vertexCount * 2];
		for (int32 i = 0; i < k_segments; ++i)
		{
			b2Vec2 v = center + radius * b2Vec2(cos(theta), sin(theta));
			glVertex2f(v.x * 30, v.y * 30);
			theta += k_increment;
		}
		glEnd();

		DrawSegment(center, center + radius * axis, color);
	}

	void BUZZ::DebugRenderer::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
	{
		glColor4f(color.r, color.g, color.b, 1);
		glBegin(GL_LINES);
		glVertex2f(p1.x * 30, p1.y * 30);
		glVertex2f(p2.x * 30, p2.y * 30);
		glEnd();
	}

	void BUZZ::DebugRenderer::DrawTransform(const b2Transform & xf)
	{
		b2Vec2 p1 = xf.p, p2;
		const float32 k_axisScale = 0.0f;

		p2 = p1 + k_axisScale * xf.q.GetXAxis();
		DrawSegment(p1, p2, b2Color(1, 0, 0));

		p2 = p1 + k_axisScale * xf.q.GetYAxis();
		DrawSegment(p1, p2, b2Color(0, 1, 0));
	}

	void BUZZ::DebugRenderer::DrawPoint(const b2Vec2 & p, float32 size, const b2Color & color)
	{
		glColor4f(color.r, color.g, color.b, 1);
		glPointSize(1.0f);
		glBegin(GL_POINTS);
		glVertex2f(p.x * 30, p.y * 30);
		glEnd();
	}
}