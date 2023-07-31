#include "bapch.h"
#include "SFUtils.h"

#include "Log.h"

sf::Texture* SFUtils::LoadTexture(const std::filesystem::path& path, const std::filesystem::path& errorPath)
{
	std::filesystem::path loadPath = path;
	if (!std::filesystem::exists(loadPath))
	{
		PA_LOG_WARN("Texture at path '{0}' not found. Using error texture instead.", loadPath.string());
		loadPath = errorPath;
	}

	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(loadPath.string()))
	{
		PA_LOG_ERROR("Failed to load texture from path '{0}'.", loadPath.string());
	}

	return texture;
}
