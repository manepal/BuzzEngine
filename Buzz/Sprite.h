#ifndef SPRITE_H
#define SPRITE_H


#include <GL\glew.h>
#include <glm\glm.hpp>

#include <string>
#include <memory>

#include "Texture2D.h"
#include "Vertex.h"


namespace BUZZ
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(GLubyte R, GLubyte g, GLubyte b, GLubyte a);
		Sprite(const std::string& texturePath);
		Sprite(const std::string& texturePath, int width, int height);

		~Sprite();

		void load();
		void draw();

		// getters
		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

	private:
		std::string m_texturePath;
		int m_width;
		int m_height;
		bool m_preserveTextureDimensions = true;

		std::shared_ptr<Texture2D> m_texture;

		GLuint m_vbo;
		GLuint m_ibo;
		GLuint m_vao;

		glm::vec3 m_position;
		Color m_color;

		static GLushort m_indices[6];
	};
}


#endif // SPRITE_H