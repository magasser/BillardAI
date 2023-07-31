#pragma once

#define TABLE_SLATE_LENGTH 254.0f
#define TABLE_SLATE_WIDTH 127.0f

#include <box2d/box2d.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Table
{
public:
	Table(const std::shared_ptr<b2World> world);
	~Table() = default;

	void Render() const;

private:
	std::vector<b2Body*> m_Pockets;
	std::vector<b2Body*> m_Cushions;
	std::unique_ptr<sf::Texture> m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
};
