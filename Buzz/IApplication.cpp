#include "IApplication.h"

namespace BUZZ
{
	const std::string & IApplication::getTitle() const
	{
		return mAppTitle;
	}

	int IApplication::getWidth() const
	{
		return mWindowWidth;
	}

	int IApplication::getHeight() const
	{
		return mWindowHeight;
	}

	bool IApplication::isFullScreen() const
	{
		return mIsFullscreen;
	}
}