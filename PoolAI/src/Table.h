#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Log.h"
#include "B2Utils.h"
#include "GameObject.h"

#define TABLE_SLATE_LENGTH 254.0f
#define TABLE_SLATE_WIDTH 127.0f
#define TABLE_RAIL_THICKNESS 18.5f
#define TABLE_LENGTH (TABLE_SLATE_LENGTH + TABLE_RAIL_THICKNESS)
#define TABLE_WIDTH (TABLE_SLATE_WIDTH + TABLE_RAIL_THICKNESS)

#define POCKET_RADIUS 4.0f

class Pocket : public GameObject
{
public:
	Pocket(const std::shared_ptr<b2World>& world, b2Vec2 position)
	{
		m_Body = B2Utils::CreateCircleBody(world, this, position, POCKET_RADIUS, 0.0f, 0.0f, 0.0f, true, b2_staticBody);
	}

private:
	b2Body* m_Body;
};

class Cushion : public GameObject
{
public:
	Cushion(const std::shared_ptr<b2World>& world, b2Vec2 position, b2Vec2* points, int32_t count)
	{
		m_Body = B2Utils::CreatePolygonBody(world, this, position, points, count, 0.0f, 0.0f, 0.0f, false, b2_staticBody);
	}

private:
	b2Body* m_Body;
};

class Table
{
public:
	Table(const std::shared_ptr<b2World>& world);
	~Table() = default;

	inline b2Vec2 GetFootSpot() const { return m_FootSpot; }
	inline b2Vec2 GetHeadSpot() const { return m_HeadSpot; }

	void Render() const;

private:
	b2Vec2 m_FootSpot;
	b2Vec2 m_HeadSpot;
	std::vector<std::unique_ptr<Pocket>> m_Pockets;
	std::vector<std::unique_ptr<Cushion>> m_Cushions;
	std::unique_ptr<sf::Texture> m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
};
