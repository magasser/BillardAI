#include "bapch.h"
#include "Ball.h"

#include "Log.h"
#include "B2Utils.h"
#include "SFUtils.h"
#include "Renderer.h"

Ball::Ball(const std::shared_ptr<b2World>& world, uint32_t number) : m_Number(number)
{
	m_Body = B2Utils::CreateCircleBody(world, b2Vec2_zero, BALL_RADIUS, BALL_DENSITY, BALL_FRICTION);

	m_Texture.reset(SFUtils::LoadTexture(std::format("assets/pool/{}.png", m_Number), "assets/pool/error.png"));
	m_Sprite = std::make_unique<sf::Sprite>();
	m_Sprite->setTexture(*m_Texture);

	sf::Vector2u textureSize = m_Texture->getSize();
	sf::Vector2f scaleFactor = Renderer::WorldPointToRenderPoint(b2Vec2(BALL_DIAMETER / textureSize.x, BALL_DIAMETER / textureSize.y));
	m_Sprite->setScale(scaleFactor);
}

void Ball::Render() const
{
	const b2Vec2& worldPosition = m_Body->GetPosition();
	m_Sprite->setPosition(Renderer::WorldPointToRenderPoint(worldPosition));

	Renderer::Draw(*m_Sprite);
}
