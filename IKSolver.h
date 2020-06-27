#pragma once

#include <vector>
#include "RobotArm.h"

class IKSolver {
public:
	void setGoalPos(std::vector<float>* pos);

	RobotArm findCPos();
private:
	std::vector<float>* goalPos;
};

