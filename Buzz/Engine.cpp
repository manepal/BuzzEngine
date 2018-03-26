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
		m_application = application;

		if (!glfwInit())
		{
			std::cerr << "failed to initialize GLFW!" << std::endl;
			return false;
		}

		if (!m_window->initialize(m_application->getTitle(), m_application->getWidth(), m_application->getHeight(), m_application->isFullScreen()))
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
		m_application->startup();

		while (!glfwWindowShouldClose(m_window->getWindowHandle()))
		{
			glfwPollEvents();

			// ---------- limit fps to max fps ----------
			// this loop delays program execution to acquire desired fps
			static float previousTime = glfwGetTime();
			do
			{
				m_currentTime = glfwGetTime();
				// calculate delta time
				m_deltaTime = m_currentTime - previousTime;
			} while (m_deltaTime < 1.0f / MAX_FPS);

			calculateFPS();
			showFPS(0.5f);
			previousTime = m_currentTime;
			// ------------------------------------------

			m_application->update(m_deltaTime);
			// draw everything on the screen
			render();
		}

		m_application->shutdown();
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

		frameTimes[currentFrame % NUM_SAMPLES] = m_deltaTime;

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
			m_fps = 1.0f / frameTimeAverage;
		}
		else
		{
			m_fps = 0.0f;
		}
	}

	void Engine::showFPS(float interval)
	{
		// display fps twice every second
		static float elapsedTime = 0.0f;
		elapsedTime += m_deltaTime;

		if (elapsedTime >= interval)
		{
			std::ostringstream outs;
			outs.precision(3);
			outs << std::fixed
				<< ": " << m_window->getWidth() << "x" << m_window->getHeight() << "    "
				<< "FPS: " << m_fps << "   ";

			m_window->appendTitle(outs.str());

			elapsedTime = 0.0f;
		}
	}

	void Engine::render()
	{
		glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_application->render();

		glfwSwapBuffers(m_window->getWindowHandle());
	}
}