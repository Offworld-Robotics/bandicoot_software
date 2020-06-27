#pragma once

#include "Segment.h"

class Lever : public Segment {
public:
	Lever(float, float, float);
	Lever(float, float, float, float, float);

	void calculateEndDirection(std::vector<float>*);
	void generateCollision(std::vector<float>, std::vector<float>, float);
};

