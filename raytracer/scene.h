#pragma once
#include "math3d.h"
#include "light.h"
#include "obstacles.h"
#include "materials.h"
#include <iostream>
#include <memory>
#include <limits>
#include <algorithm>

#include <vector>
struct Scene {
	void add_sphere(const Vec3f& center, float radius, const Material& material);
	void add_light_source(const Vec3f& position, float intensity);
	std::vector<std::unique_ptr<Obstacle>> obstacles;
	std::vector<std::unique_ptr<LightSource>> lights;

	//cast ray to k-th obstacle in direction dir and get color if ray intersects the obstacle
	//if does not intersect returns { -1, -1, -1 }
	bool cast_ray(const Vec3f& origin, const Vec3f& dir, int k, unsigned int depth, float& distance, Vec3i& color);
	//calculates reflected color through recusion
	bool calc_reflected_color(const Vec3f& pixel_center, const Vec3f& reflection, int light_source_num, int reflecting_obstacle_num, unsigned int depth, Vec3i& color);
};