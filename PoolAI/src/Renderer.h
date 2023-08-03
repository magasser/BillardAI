#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#define RENDER_SCALE 5.0f

class Renderer
{
public:
	static void Draw(const sf::Drawable& drawable);
	static void Draw(const sf::Vertex* vertices, size_t vertexCount, sf::PrimitiveType type);
	inline static float WorldDistanceToRenderDistance(float distance) { return distance * RENDER_SCALE; }

	inline static sf::Vector2f WorldPointToRenderPoint(b2Vec2 point)
	{
		return sf::Vector2f(point.x * RENDER_SCALE, point.y * RENDER_SCALE);
	}

	inline static b2Vec2 RenderPointToWorldPoint(sf::Vector2f point)
	{
		return b2Vec2(point.x / RENDER_SCALE, point.y / RENDER_SCALE);
	}

	static void DrawWorldHitboxes(const std::shared_ptr<b2World> world);

	static void DrawDebugPoint(b2Vec2 position);
	static void DrawDebugRay(b2Vec2 origin, b2Vec2 direction, float distance, sf::Color color = sf::Color::Red);
};
