#include "Sphere.h"

Sphere::Sphere(std::vector<float> pos, float rad) {
	this->position = pos;
	this->radius = rad;
}

float Sphere::getRad() {
	return this->radius;
}

std::vector<float>* Sphere::getPos() {
	return &(this->position);
}
