#include "Engine.h"

#include <iostream>
#include <sstream>

const float MAX_FPS = 60.0F;

namespace BUZZ
{
	Engine* Engine::getInstance()
	{
		static Engine* instance = new Engine();
		return instance;
	}

	bool Engine::startup(IApplication * application)
	{
		mApplication = application;

		if (!glfwInit())
		{
			std::cerr << "failed to initialize GLFW!" << std::endl;
			return false;
		}

		if (!mWindow->initialize(mApplication->getTitle(), mApplication->getWidth(), mApplication->getHeight(), mApplication->isFullScreen()))
		{
			shutdown();
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
	void Engine::run()
	{
		mApplication->startup();

		while (!glfwWindowShouldClose(mWindow->getWindowHandle()))
		{
			glfwPollEvents();

			// ---------- limit fps to max fps ----------
			// this loop delays program execution to acquire desired fps
			static float previousTime = glfwGetTime();
			do
			{
				mCurrentTime = glfwGetTime();
				// calculate delta time
				mDeltaTime = mCurrentTime - previousTime;
			} while (mDeltaTime < 1.0f / MAX_FPS);

			showFPS();
			previousTime = mCurrentTime;
			// ------------------------------------------

			mApplication->update(mDeltaTime);
			mApplication->draw();
		}

		mApplication->shutdown();
		shutdown();
	}

	void Engine::shutdown()
	{
		glfwTerminate();
	}

	void Engine::showFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float previousTime = glfwGetTime();

		frameTimes[currentFrame % NUM_SAMPLES] = mDeltaTime;

		int numFrames;
		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
		{
			numFrames = currentFrame;
		}
		else
		{
			numFrames = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < numFrames; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage = frameTimeAverage / numFrames;

		if (frameTimeAverage > 0)
		{
			// time  is in seconds divide 1 frame by average time taken to render 1 frame
			mFPS = 1.0f / frameTimeAverage;
		}
		else
		{
			mFPS = 0.0f;
		}

		// display fps twice every second
		static float elapsedTime = 0.0f;
		elapsedTime += mDeltaTime;

		if (elapsedTime >= 0.5f)
		{
			std::ostringstream outs;
			outs.precision(3);
			outs << std::fixed
				<< ": " << mWindow->getWidth() << "x" << mWindow->getHeight() << "    "
				<< "FPS: " << mFPS << "   ";

			mWindow->appendTitle(outs.str());

			elapsedTime = 0.0f;
		}
	}
}