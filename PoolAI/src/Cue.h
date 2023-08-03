#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "GameObject.h"

#define CUE_WIDTH 2.0f
#define CUE_LENGTH 144.0f

class Cue : public GameObject
{
public:
	Cue(const std::shared_ptr<b2World>& world);

	void Render() const;

	constexpr float GetWidth() const { return CUE_WIDTH; }
	constexpr float GetLength() const { return CUE_LENGTH; }
	inline b2Body* GetBody() const { return m_Body; }

private:
	b2Body* m_Body;
	std::unique_ptr<sf::Texture> m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
};
