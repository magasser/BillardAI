#include "bapch.h"
#include "Table.h"

#include "B2Utils.h"
#include "SFUtils.h"
#include "Renderer.h"
#include "Settings.h"

Table::Table(const std::shared_ptr<b2World>& world)
{
	m_Texture.reset(SFUtils::LoadTexture("assets/pool/table_big.png", "assets/pool/error.png"));

	m_Sprite = std::make_unique<sf::Sprite>();
	m_Sprite->setTexture(*m_Texture);

	sf::Vector2u textureSize = m_Texture->getSize();
	sf::Vector2f scaleFactor = Renderer::WorldPointToRenderPoint(b2Vec2(TABLE_LENGTH / textureSize.x, TABLE_WIDTH / textureSize.y));
	m_Sprite->setScale(scaleFactor);

	m_Pockets.reserve(6);
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 13.0f, 13.5f }));
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 134.8f, 10.0f }));
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 257.5f, 13.5f }));
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 257.5f, 132.5f }));
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 134.8f, 135.5f }));
	m_Pockets.push_back(std::make_unique<Pocket>(world, b2Vec2{ 13.0f, 132.0f }));

	b2Vec2 c1[4] = { {-53.5f, 0.0f}, {53.5f, 0.0f}, {-49.0f, 4.0f}, {52.0f, 4.0f} };
	b2Vec2 c2[4] = { {-54.5f, 0.0f}, {54.0f, 0.0f}, {-53.0f, 4.0f}, {50.0f, 4.0f} };
	b2Vec2 c3[4] = { {0.0f, -48.0f}, {0.0f, 47.0f}, {4.0f, 51.0f}, {4.0f, -52.0f} };
	b2Vec2 c4[4] = { {-53.0f, 0.0f}, {50.0f, 0.0f}, {-54.5f, 4.0f}, {54.0f, 4.0f} };
	b2Vec2 c5[4] = { {-49.0f, 0.0f}, {52.0f, 0.0f}, {-53.5f, 4.0f}, {53.5f, 4.0f} };
	b2Vec2 c6[4] = { {0.0f, -52.0f}, {0.0f, 51.0f}, {4.0f, 47.0f}, {4.0f, -48.0f} };

	m_Cushions.reserve(6);
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 74.0f, 12.2f }, c1, 4));
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 196.0f, 12.2f }, c2, 4));
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 255.3f, 73.0f }, c3, 4));
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 196.0f, 129.5f }, c4, 4));
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 74.0f, 129.5f }, c5, 4));
	m_Cushions.push_back(std::make_unique<Cushion>(world, b2Vec2{ 13.0f, 73.0f }, c6, 4));

	m_FootSpot = b2Vec2(TABLE_LENGTH / 4, TABLE_WIDTH / 2);
	m_HeadSpot = b2Vec2(TABLE_LENGTH - TABLE_LENGTH / 4, TABLE_WIDTH / 2);
}

void Table::Render() const
{
	Renderer::Draw(*m_Sprite);
}
