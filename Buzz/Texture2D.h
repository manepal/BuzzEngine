#ifndef	TEXTURE_2D_H
#define TEXTURE_2D_H

#include <GL\glew.h>
#include <string>

namespace BUZZ
{
	class Texture2D
	{
	public:
		Texture2D();
		virtual ~Texture2D();

		bool loadTexture(const std::string& filename, bool generateMipmaps = true);
		void bind(GLuint texUnit = 0);
		void unbind(GLuint texUnit = 0);

		GLuint getId() { return m_texture; }

		// getters
		int getWidth();
		int getHeight();

	private:
		GLuint m_texture;
		int m_width;
		int m_height;
	};
}


#endif // TEXTURE_2D_H