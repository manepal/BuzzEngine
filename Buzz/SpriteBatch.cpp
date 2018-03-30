#include "SpriteBatch.h"

#include <algorithm>

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
		m_batches.clear();
	}

	void SpriteBatch::end()
	{
		if (m_glyphs.empty()) return;

		std::sort(m_glyphs.begin(), m_glyphs.end());
		createRenderBatches();
	}

	void SpriteBatch::render()
	{
		if (m_glyphs.empty()) return;

		glBindVertexArray(m_vao);

		for (auto batch : m_batches)
		{
			glBindTexture(GL_TEXTURE_2D, batch.textureID);
			//glDrawElements(GL_TRIANGLES, m_glyphs.size() * 6, GL_UNSIGNED_SHORT, 0);
			glDrawArrays(GL_TRIANGLES, batch.offset, batch.vertexCount);
		}

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

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}

	void SpriteBatch::addGlyph(const Glyph& glyph)
	{
		m_glyphs.push_back(glyph);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphs.size() * 6);

		int cv = 0;
		RenderBatch batch;
		batch.textureID = m_glyphs[0].textureID;
		batch.offset = 0;
		batch.vertexCount = 0;

		for (auto g : m_glyphs)
		{
			vertices[cv++] = g.vertices[0];
			vertices[cv++] = g.vertices[1];
			vertices[cv++] = g.vertices[2];
			vertices[cv++] = g.vertices[3];
			vertices[cv++] = g.vertices[4];
			vertices[cv++] = g.vertices[5];

			if (batch.textureID == g.textureID)
			{
				batch.vertexCount += 6;
			}
			else
			{
				m_batches.push_back(batch);
				batch.offset = batch.vertexCount;
				batch.textureID = g.textureID;
				// reset the vertex count to 6
				batch.vertexCount = 6;
			}
		}
		// push the last batch
		m_batches.push_back(batch);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
}