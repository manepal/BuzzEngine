#include "Engine.h"

#include "Window.h"

#include <iostream>

namespace BUZZ
{
	Engine* Engine::getInstance()
	{
		static Engine* instance = new Engine();
		return instance;
	}

	bool Engine::startUp(const std::string& title, int width, int height, bool fullscreen)
	{
		if (!glfwInit())
		{
			std::cerr << "failed to initialize GLFW!" << std::endl;
			return false;
		}

		mAppTitle = title;
		mWidth = width;
		mHeight = height;

		if (!BUZZ::Window::getInstance()->initialize(mAppTitle, mWidth, mHeight, fullscreen))
		{
			shutDown();
			return false;
		}

		glewExperimental = GL_TRUE;
		if (GLEW_OK != glewInit())
		{
			std::cerr << "failed to initialize GLEW!" << std::endl;
			return false;
		}

		return true;
	}
	void Engine::shutDown()
	{
		glfwTerminate();
	}
}