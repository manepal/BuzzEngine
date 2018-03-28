#include "ResourceManager.h"

#include <iostream>

namespace BUZZ
{
	std::map<std::string, std::shared_ptr<Texture2D>> ResourceManager::m_textureCache;

	const std::shared_ptr<Texture2D> ResourceManager::getTexture(const std::string & texturePath)
	{
		// look for texture in the map
		auto iterator = m_textureCache.find(texturePath);

		if (iterator != m_textureCache.end()) // found
		{
			//std::cout << "'" << texturePath << "' loaded from texture cache." << std::endl;
			return iterator->second;
		}

		//std::cout << "'" << texturePath << "' loaded from disk." << std::endl;

		std::shared_ptr<Texture2D> newTexture(new Texture2D);
		if (newTexture->loadTexture(texturePath) == false)
		{
			return nullptr;
		}

		m_textureCache.insert(std::pair<std::string, std::shared_ptr<Texture2D>>(texturePath, newTexture));

		return newTexture;
	}
}