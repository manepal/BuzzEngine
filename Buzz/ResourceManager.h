#ifndef  RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H


#include <map>
#include <string>
#include <memory>

#include "Texture2D.h"

namespace BUZZ
{
	class ResourceManager
	{
	public:
		static const std::shared_ptr<Texture2D> getTexture(const std::string& texturePath);
	private:
		static std::map<std::string, std::shared_ptr<Texture2D>> m_textureCache;
	};
}


#endif // RESOURCE_MANAGER_H