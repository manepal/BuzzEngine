#include "Input.h"

#include "Window.h"

namespace BUZZ
{
	bool BUZZ::Input::getKeyDown(GLushort key)
	{
		if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), key) == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}

	bool Input::getKeyUp(GLushort key)
	{
		if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), key) == GLFW_RELEASE)
		{
			return true;
		}

		return false;
	}
}
