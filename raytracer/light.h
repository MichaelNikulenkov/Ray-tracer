#pragma once
#include "math3d.h"

struct LightSource {
	LightSource(Vec3f position, float intensity);
	Vec3f position = { 0, 0, 0 };
	float intensity = 1;
};