#pragma once

#include <vector>

class Sphere {
public:
	Sphere(std::vector<float>, float);

	float getRad();
	std::vector<float>* getPos();

private:
	std::vector<float> position;
	float radius;
};

