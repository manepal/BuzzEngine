#ifndef	ENGINE_H
#define ENGINE_H

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#include "IApplication.h"
#include "Window.h"

namespace BUZZ
{
	class Engine
	{
	public:
		static Engine* getInstance();

		bool startup(IApplication* application);
		void run();
		void shutdown();

	private:
		Engine() {
			m_window = Window::getInstance();
		}

		IApplication* m_application;
		Window* m_window;

		float m_fps;
		float m_deltaTime;
		float m_currentTime;
		float m_previousTime;

		void calculateFPS();
		void showFPS(float interval);

		void render();
	};
}


#endif // ENGINE_H