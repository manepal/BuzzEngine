#include "Sprite.h"

#include <iostream>

#include "Vertex.h"
#include "ResourceManager.h"


namespace BUZZ
{
	GLushort Sprite::m_indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

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

			m_width = m_texture->getWidth();
			m_height = m_texture->getHeight();
		}

		Vertex vertices[4];
		float x = m_width / 2.0f;
		float y = m_height / 2.0f;

		// top left
		vertices[0].setPosition(-x, y);
		vertices[0].setUV(0.0f, 1.0f);
		vertices[0].setColor(m_color.r, m_color.g, m_color.b, m_color.a);

		// top right
		vertices[1].setPosition(x, y);
		vertices[1].setUV(1.0f, 1.0f);
		vertices[1].setColor(m_color.r, m_color.g, m_color.b, m_color.a);

		// bottom right
		vertices[2].setPosition(x, -y);
		vertices[2].setUV(1.0f, 0.0f);
		vertices[2].setColor(m_color.r, m_color.g, m_color.b, m_color.a);

		// bottom left
		vertices[3].setPosition(-x, -y);
		vertices[3].setUV(0.0f, 0.0f);
		vertices[3].setColor(m_color.r, m_color.g, m_color.b, m_color.a);

		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), nullptr);
		glEnableVertexAttribArray(0);

		// texcoords attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Position)));
		glEnableVertexAttribArray(1);

		// color attribute
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)(sizeof(Position) + sizeof(UV)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Sprite::draw()
	{
		/*if (mTexture == nullptr)
		{
			return;
		}
		*/
		glBindVertexArray(m_vao);

		if (m_texture != nullptr)
			m_texture->bind(0);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		
		if (m_texture != nullptr )
			m_texture->unbind(0);
		
		glBindVertexArray(0);
	}
}