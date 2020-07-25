#pragma once
#include "math3d.h"

struct Material {
	Material(float albedo, int n_specular, float Kd, float Ks, float Kr, unsigned int depth, Vec3i color);
	//the measure of the diffuse reflection
	float albedo;
	//Higher n results in smaller, tighter specular highlight
	int n_specular;
	//diffuse intensity multiplier
	float Kd;
	//specular intensity multiplier
	float Ks;
	//reflection multiplier
	float Kr;
	//reflection depth
	unsigned int depth;
	//color
	Vec3i color;
};


const Material ICE_MATERIAL = Material(0.7f, 70, 1.0f, 30.0f, 1.0f, 4, Vec3i(40, 60, 77));
const Material SHINY_CRIMSON_MATERIAL = Material(0.7f, 70, 1.0f, 30.0f, 1.0f, 4, Vec3i(220, 20, 60));