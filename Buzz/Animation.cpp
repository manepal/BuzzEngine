#include "Animation.h"

#include <GLFW\glfw3.h>

namespace BUZZ
{
	Animation::Animation(float interval) :
		m_interval(interval),
		m_currentFrameIndex(0)
	{
	}

	Animation::~Animation()
	{
		m_frames.clear();
	}

	void Animation::addFrame(const std::string& texturePath)
	{
		std::shared_ptr<Sprite> animFrame(new Sprite(texturePath));
		animFrame->load();

		m_frames.push_back(animFrame);
	}

	void Animation::setInterval(float interval)
	{
		m_interval = interval;
	}

	void Animation::reset()
	{
		m_currentFrameIndex = 0;
	}

	void Animation::update(float dt)
	{
		static float duration = 0.0f;

		duration += dt;

		if (duration >= m_interval)
		{
			m_currentFrameIndex++;
			m_currentFrameIndex %= m_frames.size();
			duration = 0.0f;
		}
	}

	void Animation::draw()
	{
		//m_frames[m_currentFrameIndex]->draw();
	}
}