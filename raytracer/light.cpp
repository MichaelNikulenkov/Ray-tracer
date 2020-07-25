#include "light.h"

LightSource::LightSource(Vec3f position, float intensity) {
	this->position = position;
	this->intensity = intensity;
}