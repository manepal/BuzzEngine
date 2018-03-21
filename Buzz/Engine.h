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
			mWindow = Window::getInstance();
		}

		IApplication* mApplication;
		Window* mWindow;

		float mFPS;
		float mDeltaTime;
		float mCurrentTime;
		float mPreviousTime;

		void calculateFPS();
		void showFPS(float interval);

		void render();
	};
}


#endif // ENGINE_H