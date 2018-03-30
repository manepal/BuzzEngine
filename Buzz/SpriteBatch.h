#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H


#include <GL\glew.h>

#include <vector>
#include <memory>

#include "Vertex.h"
#include "Sprite.h"

namespace BUZZ
{
	struct Glyph;

	struct RenderBatch
	{
	public:
		int offset;
		int vertexCount;
		GLuint textureID;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin();
		void end();
		void render();

	private:
		GLuint m_vbo;
		GLuint m_ibo;
		GLuint m_vao;

		std::vector<Glyph> m_glyphs;
		std::vector<RenderBatch> m_batches;

	private:
		friend class Sprite;

		void createVertexArray();
		void addGlyph(const Glyph& glyph);
		void createRenderBatches();
	};
}


#endif // !SPRITE_BATCH_H