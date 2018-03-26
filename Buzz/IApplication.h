#ifndef I_APPLICATION_H
#define I_APPLICATION_H


#include <string>

#include "ShaderProgram.h"
#include "Camera.h"

namespace BUZZ
{
	class IApplication
	{
	public:
		virtual void startup() = 0;
		virtual void update(float dt) = 0;
		virtual void render() = 0;
		virtual void shutdown() = 0;

		const std::string& getTitle() const;
		int getWidth() const;
		int getHeight() const;
		bool isFullScreen() const;

	protected:
		int m_windowWidth;
		int m_windowHeight;
		std::string m_appTitle;
		bool m_isFullscreen;

		BUZZ::Camera m_camera;
	};
}


#endif // !APPLICATION_H
