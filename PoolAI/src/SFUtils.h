#pragma once

#include <SFML/Graphics/Texture.hpp>

class SFUtils
{
public:
	static sf::Texture* LoadTexture(const std::filesystem::path& path, const std::filesystem::path& errorPath);
};
