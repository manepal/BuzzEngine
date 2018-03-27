#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H


#include <GL\glew.h>

#include <vector>

#include "Vertex.h"
#include "Sprite.h"

namespace BUZZ
{
	class Glyph;

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

	private:
		friend class Sprite;

		void createVertexArray();
		void addGlyph(const Glyph& glyph);
	};
}


#endif // !SPRITE_BATCH_H