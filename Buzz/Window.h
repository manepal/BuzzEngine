#ifndef WINDOW_H
#define WINDOW_H


#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>


namespace BUZZ
{
	// singleton window class
	class Window
	{
	public:
		// returns singleton instance of window
		static Window* getInstance();

		bool initialize(const std::string&  title, int width, int height, bool fullscreen = false);
		void close();

		GLFWwindow* getWindowHandle() const;
		int getWidth() const;
		int getHeight() const;

		void setTitle(const std::string& title);
		void setWindowSize(int width, int height);
		// this appends the suppkied value to the current title
		void appendTitle(const std::string& str);

	private:
		Window();
		~Window();

		void setWindowCallbacks();
		static void glfw_OnFrameBufferSize(GLFWwindow* window, int width, int height);
	
	private:
		GLFWwindow * m_window;

		std::string m_title;
		int m_width;
		int m_height;
		bool m_isFullscreen;
	};
}


#endif // WINDOW_H