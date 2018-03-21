#ifndef	ENGINE_H
#define ENGINE_H

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

namespace BUZZ
{
	class Engine
	{
	public:
		static Engine* getInstance();

		bool startUp(const std::string& title, int width, int height, bool fullscreen = false);
		void shutDown();

	private:
		Engine() {}

		std::string mAppTitle;
		int mWidth;
		int mHeight;
	};
}


#endif // ENGINE_H