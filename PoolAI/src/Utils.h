#pragma once

#define PI 3.1415927f
#define DEG_TO_RAD (PI / 180.0f)
#define RAD_TO_DEG (180.0f / PI)


class Utils
{
public:
	inline static float DegToRad(float degrees) { return degrees * DEG_TO_RAD; }
	inline static float RadToDeg(float radians) { return radians * RAD_TO_DEG; }
	
};
