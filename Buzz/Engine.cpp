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

			calculateFPS();
			showFPS(0.5f);
			previousTime = mCurrentTime;
			// ------------------------------------------

			mApplication->update(mDeltaTime);
			// draw everything on the screen
			render();
		}

		mApplication->shutdown();
		shutdown();
	}

	void Engine::shutdown()
	{
		glfwTerminate();
	}

	void Engine::calculateFPS()
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
	}

	void Engine::showFPS(float interval)
	{
		// display fps twice every second
		static float elapsedTime = 0.0f;
		elapsedTime += mDeltaTime;

		if (elapsedTime >= interval)
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

	void Engine::render()
	{
		glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mApplication->render();

		glfwSwapBuffers(mWindow->getWindowHandle());
	}
}