#include "bapch.h"
#include "B2Utils.h"

#include "Renderer.h"

b2Body* B2Utils::CreateCircleBody(const std::shared_ptr<b2World>& world,
                                                  b2Vec2 position,
                                                  float radius,
                                                  float density,
                                                  float friction,
                                                  b2BodyType bodyType)
{
	b2Body* body = CreateBody(world, position, bodyType);

	b2CircleShape circle;
	circle.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* B2Utils::CreateRectBody(const std::shared_ptr<b2World>& world,
                                                b2Vec2 position,
                                                float width,
                                                float height,
                                                float density,
                                                float friction,
                                                b2BodyType bodyType)
{
	b2Body* body = CreateBody(world, position, bodyType);

	b2PolygonShape rect;
	rect.SetAsBox(width, height);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rect;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* B2Utils::CreateBody(const std::shared_ptr<b2World>& world, b2Vec2 position, b2BodyType bodyType)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	return world->CreateBody(&bodyDef);
}
