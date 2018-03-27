#include "Sprite.h"

#include <iostream>
#include <glm\gtc\matrix_transform.hpp>

#include "Vertex.h"
#include "ResourceManager.h"
#include "Engine.h"

namespace BUZZ
{
	Sprite::Sprite() :
		m_vbo(0),
		m_ibo(0),
		m_vao(0),
		m_position(glm::vec3(0.0f))
	{
		m_color.r = 255;
		m_color.g = 255;
		m_color.b = 255;
		m_color.a = 255;

		m_width = 50.0f;
		m_height = 50.0f;

		m_texturePath = "";
	}

	Sprite::Sprite(GLubyte r, GLubyte g, GLubyte b, GLubyte a):
		m_vbo(0),
		m_ibo(0),
		m_vao(0),
		m_position(glm::vec3(0.0f))
	{
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
		m_color.a = a;
		
		m_width = 50.0f;
		m_height = 50.0f;

		m_texturePath = "";
	}

	Sprite::Sprite(const std::string & texturePath):
		m_vbo(0),
		m_ibo(0),
		m_vao(0),
		m_position(glm::vec3(0.0f))
	{
		m_color.r = 255;
		m_color.g = 255;
		m_color.b = 255;
		m_color.a = 255;

		m_texturePath = texturePath;
	}

	Sprite::Sprite(const std::string & texturePath, int width, int height):
		m_vbo(0),
		m_ibo(0),
		m_vao(0),
		m_position(glm::vec3(0.0f))
	{
		m_color.r = 255;
		m_color.g = 255;
		m_color.b = 255;
		m_color.a = 255;

		m_preserveTextureDimensions = false;
		m_texturePath = texturePath;
		m_width = width;
		m_height = height;
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
		glDeleteVertexArrays(1, &m_vao);

		m_vbo = 0;
		m_ibo = 0;
		m_vao = 0;
	}

	void Sprite::load()
	{
		//m_texturePath = texturePath;

		if (m_texturePath != "")
		{
			m_texture = ResourceManager::getTexture(m_texturePath);
			if (m_texture == nullptr)
			{
				std::cerr << "texture '" << m_texturePath << "' not loaded! sprite will be initialized without a texture!" << std::endl;
			}

			if (m_preserveTextureDimensions)
			{
				m_width = m_texture->getWidth();
				m_height = m_texture->getHeight();
			}
		}
	}

	void Sprite::draw(const glm::mat4& model)
	{
		Glyph glyph;
		glyph.textureID = m_texture->getId();

		float x = m_width / 2.0f;
		float y = m_height / 2.0f;

		glm::vec4 positions[6];
		positions[0] = glm::vec4(-x, y, 0.0f, 1.0f);
		positions[1] = glm::vec4(x, y, 0.0f, 1.0f);
		positions[2] = glm::vec4(x, -y, 0.0f, 1.0f);
		positions[3] = positions[2];
		positions[4] = glm::vec4(-x, -y, 0.0f, 1.0f);
		positions[5] = positions[0];

		for (int i = 0; i < 6; i++)
		{
			glm::vec4 pos = positions[i];
			pos = model * pos;
			glyph.vertices[i].position.set(pos.x, pos.y);
		}

		glyph.vertices[0].uv.set(0.0f, 1.0f);
		glyph.vertices[0].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		glyph.vertices[1].uv.set(1.0f, 1.0f);
		glyph.vertices[1].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		glyph.vertices[2].uv.set(1.0f, 0.0f);
		glyph.vertices[2].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		glyph.vertices[3].uv.set(1.0f, 0.0f);
		glyph.vertices[3].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		glyph.vertices[4].uv.set(0.0f, 0.0f);
		glyph.vertices[4].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		glyph.vertices[5].uv.set(0.0f, 1.0f);
		glyph.vertices[5].color.set(m_color.r, m_color.g, m_color.b, m_color.a);

		Engine::getInstance()->spriteBatch->addGlyph(glyph);
	}
}