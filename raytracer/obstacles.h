#pragma once
#include "math3d.h"
#include "materials.h"

struct Obstacle {
	//x - point of intersection. Is set to { 0, 0, 0 } if there is no intersection
	virtual bool ray_intersects(const Vec3f& origin, const Vec3f& dir, Vec3f& x) = 0;
	virtual bool ray_intersects(const Vec3f& origin, const Vec3f& dir) = 0;
	//calculate norm vector at given point
	virtual void calc_norm(const Vec3f& point, Vec3f& norm) = 0;
	//the measure of the diffuse reflection
	float albedo = 0.0f;
	//higher n results in smaller, tighter specular highlight
	int n_specular = 1;
	//to adjust the diffusiont intensity
	float Kd = 0.0f;
	//to adjust the specular highlight intensity
	float Ks = 0.0f;
	//to adjust reflections
	float Kr = 0.0f;
	//reflection depth
	unsigned int depth = 0;
	//color
	Vec3i color = { 0, 0, 0 };
};

struct Sphere : Obstacle {
	Sphere(Vec3f center, float radius, const Material& material);

	bool ray_intersects(const Vec3f& origin, const Vec3f& dir, Vec3f& x) override;
	bool ray_intersects(const Vec3f& origin, const Vec3f& dir) override;
	void calc_norm(const Vec3f& point, Vec3f& norm) override;
	Vec3f center = { 0.0f, 0.0f, 0.0f };
	float radius = 0.0f;
};