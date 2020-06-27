#include "IKSolver.h"

void IKSolver::setGoalPos(std::vector<float>* pos) {
	this->goalPos = pos;
}

RobotArm IKSolver::findCPos() {
	return RobotArm();
}
