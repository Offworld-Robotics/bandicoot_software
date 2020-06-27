#include "CollisionObject.h"

int CollisionObject::getNSpheres() {
	return this->spheres.size();
}

Sphere* CollisionObject::getSphere(int index) {
	return &(this->spheres[index]);
}

void CollisionObject::addSphere(std::vector<float> pos, float rad) {
	this->spheres.push_back(Sphere(pos, rad));
}
