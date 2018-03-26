#include "IApplication.h"

namespace BUZZ
{
	const std::string & IApplication::getTitle() const
	{
		return m_appTitle;
	}

	int IApplication::getWidth() const
	{
		return m_windowWidth;
	}

	int IApplication::getHeight() const
	{
		return m_windowHeight;
	}

	bool IApplication::isFullScreen() const
	{
		return m_isFullscreen;
	}
}