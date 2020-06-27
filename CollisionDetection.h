#pragma once

#include "RobotArm.h"
#include "SLAMInterface.h"

class CollisionDetection {
public:
	void setInterface(SLAMInterface*);
	void setArmRep(RobotArm*);

	bool collision(float);

private:
	SLAMInterface* worldInterface;
	RobotArm* armRep;

	Octree* minEncompasingCube(Octree*, Sphere*);
	bool cubeContainsSphere(std::vector<float>, float, Sphere*);

	bool treeCollidesSphere(Octree*, Sphere*);
};

