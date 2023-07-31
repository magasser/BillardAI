#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics/Drawable.hpp>

#define RENDER_SCALE 5.0f

class Renderer
{
public:
	static void Draw(const sf::Drawable& drawable);
	inline static float WorldDistanceToRenderDistance(float distance);
	inline static sf::Vector2f WorldPointToRenderPoint(b2Vec2 point);
	static void DrawWorldHitboxes(const std::shared_ptr<b2World> world);
	
};
