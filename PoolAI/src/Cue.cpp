#include "bapch.h"
#include "Cue.h"

#include "Utils.h"
#include "B2Utils.h"
#include "SFUtils.h"
#include "Renderer.h"

Cue::Cue(const std::shared_ptr<b2World>& world)
{
	m_Body = B2Utils::CreateRectBody(world, this, b2Vec2_zero, CUE_LENGTH, CUE_WIDTH, 0.0f, 0.0f, 0.0f, true, b2_staticBody);

	m_Texture.reset(SFUtils::LoadTexture("assets/pool/cue.png", "assets/pool/error.png"));
	m_Sprite = std::make_unique<sf::Sprite>();
	m_Sprite->setTexture(*m_Texture);

	sf::Vector2u textureSize = m_Texture->getSize();
	sf::Vector2f scaleFactor = Renderer::WorldPointToRenderPoint(b2Vec2(CUE_LENGTH / textureSize.x, CUE_WIDTH / textureSize.y));
	m_Sprite->setScale(scaleFactor);
}

void Cue::Render() const
{
	const b2Vec2& worldPosition = m_Body->GetPosition();
	const b2Vec2 size = B2Utils::GetBodySize(m_Body);

	m_Sprite->setPosition(Renderer::WorldPointToRenderPoint(worldPosition));
	m_Sprite->setRotation(Utils::RadToDeg(m_Body->GetAngle()));
	m_Sprite->setOrigin(size.x, size.y);

	Renderer::Draw(*m_Sprite);
}
