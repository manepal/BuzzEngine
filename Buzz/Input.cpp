#include "Input.h"

#include "Window.h"

#include <iostream>

namespace BUZZ
{
	//glm::vec2 Input::m_cursorPos = glm::vec2(0.0f);
	/*int Input::m_previousState = GLFW_RELEASE;
	int Input::m_currentState = GLFW_RELEASE;*/

	bool BUZZ::Input::getKeyDown(GLushort key)
	{
		if (glfwGetKey(Window::getInstance()->getWindowHandle(), key) == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}

	bool Input::getKeyUp(GLushort key)
	{
		if (glfwGetKey(Window::getInstance()->getWindowHandle(), key) == GLFW_RELEASE)
		{
			return true;
		}

		return false;
	}

	bool Input::getMouseDown(GLushort button)
	{
		if (glfwGetMouseButton(Window::getInstance()->getWindowHandle(), button) == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}

	bool Input::getMouseUp(GLushort button)
	{
		if (glfwGetMouseButton(Window::getInstance()->getWindowHandle(), button) == GLFW_RELEASE)
		{

			return true;
		}
		
		return false;
	}

	const glm::vec2 & Input::getCursorPos()
	{
		double x, y;
		glfwGetCursorPos(Window::getInstance()->getWindowHandle(), &x, &y);

		// convert screen coordinates to world space coordinates
		x = x - (Window::getInstance()->getWidth() / 2.0f);
		y = (Window::getInstance()->getHeight() / 2.0f) - y;

		//return m_cursorPos;

		return glm::vec2(x, y);
	}

	void Input::setKeyCallbacks()
	{
		glfwSetKeyCallback(Window::getInstance()->getWindowHandle(), onKey);
		glfwSetMouseButtonCallback(Window::getInstance()->getWindowHandle(), onMouseButton);
		glfwSetInputMode(Window::getInstance()->getWindowHandle(), GLFW_STICKY_MOUSE_BUTTONS, 1);
		//glfwSetCursorPosCallback(Window::getInstance()->getWindowHandle(), onMouseMove);
		glfwSetScrollCallback(Window::getInstance()->getWindowHandle(), onMouseScroll);
	}

	void Input::onMouseButton(GLFWwindow * window, int button, int action, int mods)
	{
		/*m_previousState = m_currentState;
		m_currentState = action;*/
	}

	void Input::onKey(GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	//void Input::onMouseMove(GLFWwindow * window, double posX, double posY)
	//{
	//	double x, y;
	//	glfwGetCursorPos(Window::getInstance()->getWindowHandle(), &x, &y);


	//	// convert screen coordinates to world space coordinates
	//	x = x - (Window::getInstance()->getWidth() / 2.0f);
	//	y = (Window::getInstance()->getHeight() / 2.0f) - y;

	//	//m_cursorPos.x = x;
	//	//m_cursorPos.y = y;
	//	
	//	//std::cout << x << ", " << y << std::endl;
	//}

	void Input::onMouseScroll(GLFWwindow * window, double deltaX, double deltaY)
	{

		//std::cout << "on mouse scroll." << std::endl;
	}
}
