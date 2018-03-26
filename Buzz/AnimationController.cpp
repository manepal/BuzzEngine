#include "AnimationController.h"

#include <iostream>

namespace BUZZ
{
	AnimationController::AnimationController() :
		m_isAnimationChanged(false)
	{
	}

	AnimationController::~AnimationController()
	{
		m_animations.clear();
	}

	void AnimationController::addAnimation(const std::string& name, std::shared_ptr<Animation> animation)
	{
		m_activeAnimation = animation;

		m_animations.insert(std::pair<std::string, std::shared_ptr<Animation>>(name, animation));
	}

	void AnimationController::setActiveAnimation(const std::string & name)
	{
		if (m_activeAnimationName == name) return;

		m_activeAnimationName = name;
		m_isAnimationChanged = true;
	}

	void AnimationController::update(float dt)
	{
		if (m_animations.empty()) return;

		if (m_isAnimationChanged)
		{
			auto iterator = m_animations.find(m_activeAnimationName);
			if (iterator == m_animations.end())	// not found
			{
				std::cerr << "animation '" << m_activeAnimationName << "' does not exist." << std::endl;
			}
			else
			{
				m_activeAnimation = iterator->second;
				m_activeAnimation->reset();
			}

			m_isAnimationChanged = false;
		}

		m_activeAnimation->update(dt);
	}

	void AnimationController::draw()
	{
		if (m_animations.empty()) return;

		m_activeAnimation->draw();
	}
}