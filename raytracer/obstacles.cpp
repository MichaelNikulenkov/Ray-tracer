#pragma once
#include "obstacles.h"

Sphere::Sphere(Vec3f center, float radius, const Material& material) {
	this->Ks = material.Ks;
	this->Kd = material.Kd;
	this->Kr = material.Kr;
	this->depth = material.depth;
	this->albedo = material.albedo;
	this->n_specular = material.n_specular;
	this->center = center;
	this->radius = radius;
	this->color = material.color;
}

bool Sphere::ray_intersects(const Vec3f& origin, const Vec3f& dir, Vec3f& x) {

	//calculate projection of center on the line: t in line equation origin + dir*t 
	//intersects if distance the point of projection is greater than the radius
	float t = (dir.X*(center.X - origin.X) + dir.Y*(center.Y - origin.Y) + dir.Z*(center.Z - origin.Z))
		/ (dir.X*dir.X + dir.Y*dir.Y + dir.Z*dir.Z);

	//point of projection
	Vec3f proj = { 0.0f, 0.0f, 0.0f };
	add_mult(origin, dir, t, proj);
	//distance from sphere center to point of projection
	float dist = calc_distance(proj, center);

	//check if intersects
	bool intersects;
	dist < radius ? intersects = true : intersects = false;

	if (intersects) {
		//calculate point of intersection from Pythagoras theorem
		float ti = t - sqrtf(radius*radius - dist * dist);
		add_mult(origin, dir, ti, x);
	}
	else {
		x.X = 0.0f;
		x.Y = 0.0f;
		x.Z = 0.0f;
	}

	return intersects;
}

bool Sphere::ray_intersects(const Vec3f& origin, const Vec3f& dir) {
	//calculate projection of center on the line: t in line equation origin + dir*t 
	//intersects if distance the point of projection is greater than the radius
	float t = (dir.X*(center.X - origin.X) + dir.Y*(center.Y - origin.Y) + dir.Z*(center.Z - origin.Z))
		/ (dir.X*dir.X + dir.Y*dir.Y + dir.Z*dir.Z);

	//point of projection
	Vec3f proj = { 0.0f, 0.0f, 0.0f };
	add_mult(origin, dir, t, proj);
	//distance from sphere center to point of projection
	float dist = calc_distance(proj, center);

	//check if intersects
	bool intersects;
	dist < radius ? intersects = true : intersects = false;

	return intersects;
}

void Sphere::calc_norm(const Vec3f& point, Vec3f& norm) {
	substract(point, center, norm);
	norm.normalize();
}

