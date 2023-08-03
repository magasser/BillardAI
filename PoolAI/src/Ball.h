#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "GameObject.h"

#define BALL_RADIUS 2.85f
#define BALL_DIAMETER 5.7f
#define BALL_DENSITY 0.17f
#define BALL_FRICTION 50.0f
#define BALL_RESTITUTION 0.95f

class Ball : public GameObject
{
public:
	enum BallType
	{
		Unknown = 0,
		Solid,
		Striped,
		Cue,
		Eight,
	};
public:
	Ball(const std::shared_ptr<b2World>& world, uint32_t number);

	void Render() const;

	inline void SetEnabled(bool enabled) { m_IsEnabled = enabled; m_Body->SetEnabled(m_IsEnabled); }

	constexpr float GetRadius() const { return BALL_RADIUS; }
	inline uint32_t GetNumber() const { return m_Number; }
	inline uint32_t GetType() const { return m_Type; }
	inline bool IsEnabled() const { return m_IsEnabled; }
	inline b2Body* GetBody() const { return m_Body; }

private:
	uint32_t m_Number;
	BallType m_Type;
	bool m_IsEnabled;
	b2Body* m_Body;
	b2FrictionJoint* m_FrictionJoint;
	std::unique_ptr<sf::Texture> m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
};
