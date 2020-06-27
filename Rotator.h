#pragma once

#include "Segment.h"

class Rotator : public Segment {
public:
	Rotator(float, float, float);
	Rotator(float, float, float, float, float);

	void calculateEndDirection(std::vector<float>*);
	void generateCollision(std::vector<float>, std::vector<float>, float);
};


