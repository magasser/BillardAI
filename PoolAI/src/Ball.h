#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define BALL_RADIUS 2.85f
#define BALL_DIAMETER 5.7f
#define BALL_DENSITY 17.0f
#define BALL_FRICTION 0.0f

class Ball
{
public:
	Ball(const std::shared_ptr<b2World>& world, uint32_t number);
	~Ball() = default;

	void Render() const;

	inline uint32_t GetNumber() const { return m_Number; }
	inline b2Body* GetBody() const { return m_Body; }

private:
	uint32_t m_Number;
	b2Body* m_Body;
	std::unique_ptr<sf::Texture> m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
};
