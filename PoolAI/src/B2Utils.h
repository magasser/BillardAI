#pragma once

#include <box2d/box2d.h>

class B2Utils
{
public:
	static b2Body* CreateCircleBody(const std::shared_ptr<b2World>& world,
	                                                b2Vec2 position,
	                                                float radius,
	                                                float density,
	                                                float friction,
	                                                b2BodyType bodyType = b2_dynamicBody);
	static b2Body* CreateRectBody(const std::shared_ptr<b2World>& world,
	                                              b2Vec2 position,
	                                              float width,
	                                              float height,
	                                              float density,
	                                              float friction,
	                                              b2BodyType bodyType = b2_dynamicBody);

private:
	static b2Body* CreateBody(const std::shared_ptr<b2World>& world, b2Vec2 position, b2BodyType bodyType);
};
