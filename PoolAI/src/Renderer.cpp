#include "bapch.h"
#include "Renderer.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "App.h"

void Renderer::Draw(const sf::Drawable& drawable)
{
	App::Get().GetWindow().draw(drawable);
}

float Renderer::WorldDistanceToRenderDistance(float distance)
{
	return distance * RENDER_SCALE;
}

sf::Vector2f Renderer::WorldPointToRenderPoint(b2Vec2 point)
{
	return sf::Vector2f(point.x * RENDER_SCALE, point.y * RENDER_SCALE);
}

void Renderer::DrawWorldHitboxes(const std::shared_ptr<b2World> world)
{
	static bool initialized = false;
	static sf::CircleShape circle;
	static sf::ConvexShape polygon;

	if (!initialized)
	{
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Green);
		circle.setOutlineThickness(2.0f);
		polygon.setFillColor(sf::Color::Transparent);
		polygon.setOutlineColor(sf::Color::Green);
		polygon.setOutlineThickness(2.0f);
		initialized = true;
	}


	b2Body* bodyPtr = world->GetBodyList();
	while (bodyPtr)
	{
		b2Fixture* fixturePtr = bodyPtr->GetFixtureList();
		while (fixturePtr)
		{
			switch (fixturePtr->GetType())
			{
			case b2Shape::e_circle:
			{
				b2CircleShape* circlePtr = (b2CircleShape*)fixturePtr->GetShape();
				circle.setPosition(WorldPointToRenderPoint(bodyPtr->GetPosition()));
				circle.setRadius(WorldDistanceToRenderDistance(circlePtr->m_radius));

				Renderer::Draw(circle);
			}
			break;
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonPtr = (b2PolygonShape*)fixturePtr->GetShape();
				polygon.setPosition(WorldPointToRenderPoint(bodyPtr->GetPosition()));
				polygon.setPointCount(polygonPtr->m_count);
				for (int32_t i = 0; i < polygonPtr->m_count; ++i)
					polygon.setPoint(i, WorldPointToRenderPoint(polygonPtr->m_vertices[i]));

				Renderer::Draw(polygon);
			}
			break;
			}

			fixturePtr = fixturePtr->GetNext();
		}
		bodyPtr = bodyPtr->GetNext();
	}
}
