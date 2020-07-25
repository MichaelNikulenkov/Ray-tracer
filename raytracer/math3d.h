#pragma once
#include "math.h"

struct Vec2f {
	float X, Y;
};

struct Vec3i {
	Vec3i();
	Vec3i(int x, int y, int z);
	int R, G, B;
};

struct Vec3f {
	Vec3f(float x, float y, float z);
	Vec3f();
	float X, Y, Z;
	void normalize();
};

void add(const Vec3f& A, const Vec3f& B, Vec3f& result);
void substract(const Vec3f& A, const Vec3f& B, Vec3f& result);
void mult(const Vec3f& A, float t, Vec3f& result);
void mult(Vec3f& A, float t);
void add_mult(const Vec3f& A, const Vec3f& B, float t, Vec3f& result);
void subs_mult(const Vec3f& A, const Vec3f& B, float t, Vec3f& result);

float dot_product(const Vec3f& A, const Vec3f& B);

//calculate distance between who points
float calc_distance(const Vec3f& A, const Vec3f& B);

//calculate reflectian vector given light direction and normal to the point: R = 2(N*L)N-L
void calc_reflection(const Vec3f& light_dir, const Vec3f& normal, Vec3f& result);
