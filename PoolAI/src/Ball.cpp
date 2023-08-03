#include "bapch.h"
#include "Ball.h"

#include "B2Utils.h"
#include "SFUtils.h"
#include "Renderer.h"

Ball::Ball(const std::shared_ptr<b2World>& world, uint32_t number) : m_Number(number)
{
	m_Body = B2Utils::CreateCircleBody(world, this, b2Vec2_zero, BALL_RADIUS, BALL_DENSITY, BALL_FRICTION, BALL_RESTITUTION);
	m_FrictionJoint = B2Utils::CreateFritionJoint(world, m_Body, BALL_FRICTION);

	m_Type = m_Number == 0 ? Cue : m_Number == 8 ? Eight : m_Number < 8 ? Solid : Striped;

	m_Texture.reset(SFUtils::LoadTexture(std::format("assets/pool/{}.png", m_Number), "assets/pool/error.png"));
	m_Sprite = std::make_unique<sf::Sprite>();
	m_Sprite->setTexture(*m_Texture);

	sf::Vector2u textureSize = m_Texture->getSize();
	sf::Vector2f scaleFactor = Renderer::WorldPointToRenderPoint(
		b2Vec2(BALL_DIAMETER / textureSize.x, BALL_DIAMETER / textureSize.y));
	m_Sprite->setScale(scaleFactor);
	m_Sprite->setOrigin(m_Texture->getSize().x / 2, m_Texture->getSize().y / 2);
}

void Ball::Render() const
{
	if (!m_IsEnabled)
		return;

	const b2Vec2& worldPosition = m_Body->GetPosition();
	m_Sprite->setPosition(Renderer::WorldPointToRenderPoint(worldPosition));

	Renderer::Draw(*m_Sprite);
}
