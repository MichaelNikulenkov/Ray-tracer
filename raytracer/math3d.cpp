#include "math3d.h"

void Vec3f::normalize() {
	float length = sqrtf(X*X + Y * Y + Z * Z);
	X /= length;
	Y /= length;
	Z /= length;
}

Vec3f::Vec3f(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}

Vec3i::Vec3i(int x, int y, int z) {
	R = x;
	G = y;
	B = z;
}

Vec3i::Vec3i() {
	R = 0;
	G = 0;
	B = 0;
}

Vec3f::Vec3f() {
	X = 0;
	Y = 0;
	Z = 0;
}

void add(const Vec3f& A, const Vec3f& B, Vec3f& result) {
	result.X = A.X + B.X;
	result.Y = A.Y + B.Y;
	result.Z = A.Z + B.Z;
}

void substract(const Vec3f& A, const Vec3f& B, Vec3f& result) {
	result.X = A.X - B.X;
	result.Y = A.Y - B.Y;
	result.Z = A.Z - B.Z;
}

void mult(const Vec3f& A, float t, Vec3f& result) {
	result.X = A.X*t;
	result.Y = A.Y*t;
	result.Z = A.Z*t;
}

void mult(Vec3f& A, float t) {
	A.X *= t;
	A.Y *= t;
	A.Z *= t;
}

void add_mult(const Vec3f& A, const Vec3f& B, float t, Vec3f& result) {
	result.X = B.X*t;
	result.Y = B.Y*t;
	result.Z = B.Z*t;

	result.X += A.X;
	result.Y += A.Y;
	result.Z += A.Z;
}

void subs_mult(const Vec3f& A, const Vec3f& B, float t, Vec3f& result) {
	result.X = -B.X*t;
	result.Y = -B.Y*t;
	result.Z = -B.Z*t;

	result.X += A.X;
	result.Y += A.Y;
	result.Z += A.Z;
}

float dot_product(const Vec3f& A, const Vec3f& B) {
	return A.X*B.X + A.Y*B.Y + A.Z*B.Z;
}

float calc_distance(const Vec3f& A, const Vec3f& B) {
	return sqrtf((A.X - B.X)*(A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y) + (A.Z - B.Z)*(A.Z - B.Z));
}

void calc_reflection(const Vec3f& light_dir, const Vec3f& normal, Vec3f& result) {
	result = { 0.0f, 0.0f, 0.0f };
	subs_mult(light_dir, normal, 2.0f * dot_product(normal, light_dir), result);
	result.normalize();
}