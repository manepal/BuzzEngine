#include "SpriteBatch.h"


namespace BUZZ
{
	SpriteBatch::SpriteBatch() :
		m_vbo(0),
		m_ibo(0),
		m_vao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin()
	{
		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		if (m_glyphs.empty()) return;

		std::vector<Vertex> vertices;
		vertices.resize(m_glyphs.size() * 6);

		int cv = 0;

		for (auto g : m_glyphs)
		{
			vertices[cv++] = g.vertices[0];
			vertices[cv++] = g.vertices[1];
			vertices[cv++] = g.vertices[2];
			vertices[cv++] = g.vertices[3];
			vertices[cv++] = g.vertices[4];
			vertices[cv++] = g.vertices[5];
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::render()
	{
		if (m_glyphs.empty()) return;

		glBindVertexArray(m_vao);

		glBindTexture(GL_TEXTURE_2D, m_glyphs[0].textureID);
		//glDrawElements(GL_TRIANGLES, m_glyphs.size() * 6, GL_UNSIGNED_SHORT, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_glyphs.size() * 6);

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);

		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		if(m_ibo == 0)
		{
			glGenBuffers(1, &m_ibo);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		const GLushort indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		
		// pass the indices data to gpu
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

		// position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), nullptr);
		// uv attribute pointer
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
		// color attribute pointer
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

	}

	void SpriteBatch::addGlyph(const Glyph& glyph)
	{
		m_glyphs.push_back(glyph);
	}
}