#ifndef ANIMATION_H
#define ANIMATION_H


#include <vector>
#include <memory>

#include "Sprite.h"

namespace BUZZ
{
	class Animation
	{
	public:
		Animation(float interval);
		~Animation();

		void addFrame(const std::string& texturePath);
		// set interval in seconds
		void setInterval(float interval);

		void reset();
		void update(float dt);
		void draw();

	private:
		float m_interval;
		int m_currentFrameIndex;

		std::vector<std::shared_ptr<Sprite>> m_frames;
	};
}

#endif // ANIMATION_H