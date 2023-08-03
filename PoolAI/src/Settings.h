#pragma once

#include <box2d/box2d.h>

class Settings
{
public:
	inline static bool ShowHitboxes;
	inline static uint32_t Index;
	inline static b2Vec2 Position;
	inline static b2Vec2 Points[4];
	inline static b2Vec2 CueBallImpuse;
	inline static float Angle;
};
