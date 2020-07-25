#include "materials.h"

Material::Material(float albedo, int n_specular, float Kd, float Ks, float Kr, unsigned int depth, Vec3i color) {
	this->albedo = albedo;
	this->n_specular = n_specular;
	this->Kd = Kd;
	this->Ks = Ks;
	this->Kr = Kr;
	this->depth = depth;
	this->color = color;
}