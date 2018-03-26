#include "Window.h"

#include <iostream>

#include "Input.h"

namespace BUZZ
{
	Window::Window()
	{}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	Window* Window::getInstance()
	{
		static Window* mInstance = new Window();

		return mInstance;
	}

	bool Window::initialize(const std::string&  title, int width, int height, bool fullscreen)
	{
		m_title = title;
		m_width = width;
		m_height = height;
		m_isFullscreen = fullscreen;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWmonitor* monitor = nullptr;

		if (m_isFullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* vMode = glfwGetVideoMode(monitor);

			m_width = vMode->width;
			m_height = vMode->height;
		}
		// create window
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), monitor, nullptr);
		if (m_window == nullptr)
		{
			std::cerr << "failed to create window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_window);

		setWindowCallbacks();

		glViewport(0, 0, m_width, m_height);

		return true;
	}


	void Window::close()
	{
		glfwSetWindowShouldClose(m_window, GL_TRUE);
	}

	GLFWwindow * Window::getWindowHandle() const
	{
		return m_window;
	}

	int Window::getWidth() const
	{
		return m_width;
	}

	int Window::getHeight() const
	{
		return m_height;
	}

	void Window::setTitle(const std::string & title)
	{
		m_title = title;

		glfwSetWindowTitle(m_window, m_title.c_str());
	}

	void Window::setWindowSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

	void Window::appendTitle(const std::string & str)
	{
		std::string newTitle = m_title + str;

		glfwSetWindowTitle(m_window, newTitle.c_str());
	}

	void Window::setWindowCallbacks()
	{
		glfwSetWindowSizeCallback(m_window, glfw_OnFrameBufferSize);
		Input::setKeyCallbacks();
	}

	void Window::glfw_OnFrameBufferSize(GLFWwindow * window, int width, int height)
	{
		Window::getInstance()->setWindowSize(width, height);

		//std::cout << "Window resized." << std::endl;

		glViewport(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight());
	}
}