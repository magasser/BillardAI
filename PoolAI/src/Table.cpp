#include "bapch.h"
#include "Table.h"

#include "B2Utils.h"
#include "SFUtils.h"
#include "Renderer.h"

Table::Table(const std::shared_ptr<b2World> world)
{
	m_Texture.reset(SFUtils::LoadTexture("assets/pool/table_big.png", "assets/pool/error.png"));

	m_Sprite = std::make_unique<sf::Sprite>();
	m_Sprite->setTexture(*m_Texture);

	sf::Vector2u textureSize = m_Texture->getSize();
	sf::Vector2f scaleFactor = Renderer::WorldPointToRenderPoint(b2Vec2(TABLE_SLATE_LENGTH / textureSize.x, TABLE_SLATE_WIDTH / textureSize.y));
	m_Sprite->setScale(scaleFactor);

	m_Cushions.push_back(B2Utils::CreateRectBody(world, b2Vec2(0, 0), 100.0f, 10.0f, 0.0f, 0.0f, b2_staticBody));
}

void Table::Render() const
{
	Renderer::Draw(*m_Sprite);
}
