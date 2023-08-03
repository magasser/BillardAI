#include "bapch.h"
#include "B2Utils.h"

#include "Renderer.h"
#include "Table.h"

b2FrictionJoint* B2Utils::CreateFritionJoint(const std::shared_ptr<b2World>& world, b2Body* body, float friction)
{
	b2Body* bodyB = CreateRectBody(world,
	                               nullptr,
	                               b2Vec2_zero,
	                               TABLE_LENGTH * 2,
	                               TABLE_WIDTH * 2,
	                               0.0f,
	                               0.0f,
	                               0.0f,
	                               true,
	                               b2_staticBody);

	b2FrictionJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.bodyB = bodyB;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.SetZero();
	jointDef.localAnchorB.SetZero();
	jointDef.maxForce = friction;
	jointDef.maxTorque = 0.0f;

	return (b2FrictionJoint*)world->CreateJoint(&jointDef);
}

b2Body* B2Utils::CreateCircleBody(const std::shared_ptr<b2World>& world,
                                  GameObject* owner,
                                  b2Vec2 position,
                                  float radius,
                                  float density,
                                  float friction,
                                  float restitution,
                                  bool isSensor,
                                  b2BodyType bodyType)
{
	b2Body* body = CreateBody(world, position, bodyType);

	b2CircleShape circle;
	circle.m_radius = radius;

	CreateFixture(body, owner, &circle, density, friction, restitution, isSensor);

	return body;
}

b2Body* B2Utils::CreateRectBody(const std::shared_ptr<b2World>& world,
                                GameObject* owner,
                                b2Vec2 position,
                                float width,
                                float height,
                                float density,
                                float friction,
                                float restitution,
                                bool isSensor,
                                b2BodyType bodyType)
{
	b2Body* body = CreateBody(world, position, bodyType);

	b2PolygonShape rect;
	rect.SetAsBox(width / 2, height / 2);

	CreateFixture(body, owner, &rect, density, friction, restitution, isSensor);

	return body;
}

b2Body* B2Utils::CreatePolygonBody(const std::shared_ptr<b2World>& world,
                                   GameObject* owner,
                                   b2Vec2 position,
                                   b2Vec2* points,
                                   int32_t pointCount,
                                   float density,
                                   float friction,
                                   float restitution,
                                   bool isSensor,
                                   b2BodyType bodyType)
{
	b2Body* body = CreateBody(world, position, bodyType);

	b2PolygonShape polygon;
	polygon.Set(points, pointCount);

	CreateFixture(body, owner, &polygon, density, friction, restitution, isSensor);

	return body;
}

bool B2Utils::IsInsideBody(b2Body* body, b2Vec2 point)
{
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture)
	{
		if (fixture->TestPoint(point))
		{
			return true;
		}

		fixture = fixture->GetNext();
	}

	return false;
}

b2Vec2 B2Utils::GetBodySize(b2Body* body)
{
	b2Vec2 size = b2Vec2_zero;
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture)
	{
		b2Shape* shape = fixture->GetShape();
		switch (shape->GetType())
		{
		case b2Shape::e_circle:
		{
			b2CircleShape* circle = (b2CircleShape*)shape;

			size.Set(circle->m_radius * 2, circle->m_radius * 2);
		}
		break;
		case b2Shape::e_polygon:
		{
			b2PolygonShape* polygon = (b2PolygonShape*)shape;

			b2Vec2 min = polygon->m_vertices[0];
			b2Vec2 max = polygon->m_vertices[0];
			for (int32_t i = 1; i < polygon->m_count; ++i)
			{
				min = b2Min(min, polygon->m_vertices[i]);
				max = b2Max(max, polygon->m_vertices[i]);
			}

			size.Set(max.x - min.x, max.y - min.y);
		}
		break;
		}

		fixture = fixture->GetNext();
	}

	return size;
}

b2Body* B2Utils::CreateBody(const std::shared_ptr<b2World>& world, b2Vec2 position, b2BodyType bodyType)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	return world->CreateBody(&bodyDef);
}

b2Fixture* B2Utils::CreateFixture(b2Body* body,
                                  GameObject* owner,
                                  b2Shape* shape,
                                  float density,
                                  float friction,
                                  float restitution,
                                  bool isSensor)
{
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = isSensor;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(owner);

	return body->CreateFixture(&fixtureDef);
}
