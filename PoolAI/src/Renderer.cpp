#include "bapch.h"
#include "Renderer.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "App.h"
#include "Utils.h"

void Renderer::Draw(const sf::Drawable& drawable)
{
	App::GetWindow().draw(drawable);
}

void Renderer::Draw(const sf::Vertex* vertices, size_t vertexCount, sf::PrimitiveType type)
{
	App::GetWindow().draw(vertices, vertexCount, type);
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
		circle.setOutlineThickness(1.0f);
		polygon.setFillColor(sf::Color::Transparent);
		polygon.setOutlineColor(sf::Color::Green);
		polygon.setOutlineThickness(1.0f);
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

				float renderRadius = WorldDistanceToRenderDistance(circlePtr->m_radius);

				circle.setOrigin(renderRadius, renderRadius);
				circle.setPosition(WorldPointToRenderPoint(bodyPtr->GetPosition()));
				circle.setRadius(renderRadius);

				Draw(circle);
			}
			break;
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonPtr = (b2PolygonShape*)fixturePtr->GetShape();
				polygon.setPosition(WorldPointToRenderPoint(bodyPtr->GetPosition()));
				polygon.setPointCount(polygonPtr->m_count);
				polygon.setRotation(Utils::RadToDeg(bodyPtr->GetAngle()));

				for (int32_t i = 0; i < polygonPtr->m_count; ++i)
					polygon.setPoint(i, WorldPointToRenderPoint(polygonPtr->m_vertices[i]));

				Draw(polygon);
			}
			break;
			}

			fixturePtr = fixturePtr->GetNext();
		}
		bodyPtr = bodyPtr->GetNext();
	}
}

void Renderer::DrawDebugPoint(b2Vec2 position)
{
	static sf::CircleShape circle;

	circle.setFillColor(sf::Color::Red);
	circle.setRadius(2.0f);
	circle.setOrigin(1.0f, 1.0f);
	circle.setPosition(Renderer::WorldPointToRenderPoint(position));

	Draw(circle);
}

void Renderer::DrawDebugRay(b2Vec2 origin, b2Vec2 direction, float distance, sf::Color color)
{
	sf::Vector2f sfOrigin = Renderer::WorldPointToRenderPoint(origin);
	sf::Vector2f sfEnd = Renderer::WorldPointToRenderPoint(origin + b2Vec2(direction.x * distance, direction.y * distance));
	sf::Vertex line[] = {
		sf::Vertex(sfOrigin, color),
		sf::Vertex(sfEnd, color),
	};

	Draw(line, 2, sf::Lines);
}
