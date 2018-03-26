#ifndef ANIMATION_CONTROLLER_H
#define ANIMAITON_CONTROLLER_H


#include <map>
#include <memory>
#include <string>

#include "Animation.h"

namespace BUZZ
{
	class AnimationController
	{
	public:
		AnimationController();
		~AnimationController();

		void addAnimation(const std::string& name, std::shared_ptr<Animation> animation);
		void setActiveAnimation(const std::string& name);

		void update(float dt);
		void draw();

	private:
		std::string m_activeAnimationName;
		bool m_isAnimationChanged;
		std::shared_ptr<Animation> m_activeAnimation;

		std::map<std::string, std::shared_ptr<Animation>> m_animations;
	};
}


#endif // ANIMATION_CONTROLLER_H