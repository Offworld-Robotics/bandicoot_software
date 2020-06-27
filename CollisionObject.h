#pragma once

#include "Sphere.h"

#include <vector>

class CollisionObject {
public:
	int getNSpheres();
	Sphere* getSphere(int);

	void addSphere(std::vector<float>, float);

private:
	std::vector<Sphere> spheres;
	float precision = 0;
};

