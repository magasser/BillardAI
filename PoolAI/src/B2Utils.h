#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

class B2Utils
{
public:
	static b2FrictionJoint* CreateFritionJoint(const std::shared_ptr<b2World>& world, b2Body* body, float friction);

	static b2Body* CreateCircleBody(const std::shared_ptr<b2World>& world,
	                                GameObject* owner,
	                                b2Vec2 position,
	                                float radius,
	                                float density,
	                                float friction,
	                                float restitution,
	                                bool isSensor = false,
	                                b2BodyType bodyType = b2_dynamicBody);
	static b2Body* CreateRectBody(const std::shared_ptr<b2World>& world,
	                              GameObject* owner,
	                              b2Vec2 position,
	                              float width,
	                              float height,
	                              float density,
	                              float friction,
	                              float restitution,
	                              bool isSensor = false,
	                              b2BodyType bodyType = b2_dynamicBody);

	static b2Body* CreatePolygonBody(const std::shared_ptr<b2World>& world,
	                                 GameObject* owner,
	                                 b2Vec2 position,
	                                 b2Vec2* points,
	                                 int32_t pointCount,
	                                 float density,
	                                 float friction,
	                                 float restitution,
	                                 bool isSensor = false,
	                                 b2BodyType bodyType = b2_dynamicBody);

	static bool IsInsideBody(b2Body* body, b2Vec2 point);

	// Currently only supports bodies with 1 fixture.
	static b2Vec2 GetBodySize(b2Body* body);

private:
	static b2Body* CreateBody(const std::shared_ptr<b2World>& world, b2Vec2 position, b2BodyType bodyType);
	static b2Fixture* CreateFixture(b2Body* body,
	                                GameObject* owner,
	                                b2Shape* shape,
	                                float density,
	                                float friction,
	                                float restitution,
	                                bool isSensor);
};
