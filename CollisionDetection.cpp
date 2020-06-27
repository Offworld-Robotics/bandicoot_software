#include "CollisionDetection.h"

void CollisionDetection::setInterface(SLAMInterface* interface) {
	this->worldInterface = interface;
}

void CollisionDetection::setArmRep(RobotArm* armRep) {
	this->armRep = armRep;
}

bool CollisionDetection::collision(float precision) {
	// This will check if the arm representation will collide with itself
	// or the environment in its current position. Whenever possible it
	// will lean towards incorrect 'true', rather than 'false' to prevent
	// damage to the rover by hitting an object. As such the collision is
	// fairly conservative. This can be adjusted with 'precision', lower
	// value means better accurracy but more computation.

	//First check collision with the world

	// Only re-generate collision object if the precision has changed
	// TODO /* this might actually need to generate every time in case arm moves*/
	if (this->armRep->getCollisionPrecision() != precision) this->armRep->generateCollision(precision);

	for (int i = 0; i < this->armRep->getNSegments(); i++) {
		CollisionObject obj = this->armRep->getSegmentCollision(i);

		for (int s = 0; s < obj.getNSpheres(); s++) {
			Sphere* sphere = obj.getSphere(s);
			Octree* reducedTree = minEncompasingCube(this->worldInterface->getOctree(), sphere);

			// No collision if minimum cube is empty
			if (!reducedTree->isSolid) continue;

			// Overview: We go to the deepest level nodes in this cube that are solid
			// and we aproximate each of them with a sphere and check for collision.

			bool result = treeCollidesSphere(reducedTree, sphere);
			if (result) return true;
		}

	}

	// Second check collision with itself

	// TODO /* implement arm self-collision */

	// Only return false if all spheres from all segments are not colliding
	return false;
}

// Checks if any solid end-nodes collide with the given sphere
bool CollisionDetection::treeCollidesSphere(Octree* octree, Sphere* sphere) {
	// Empty cube
	if (!octree->isSolid()) return false;
	
	// Actual collision part
	if (this->worldInterface->isEndNode(octree)) {
		std::vector<float> cubeCentre = this->worldInterface->getNodeCoordinate(octree);
		float cubeSize = this->worldInterface->getNodeSize(octree);

		// A sphere that minimally encompases a cube of side length 'l' will have radius
		// given by r = sqrt(3) * l / 2

		// Find the vector between the centres of these two spheres and find its length
		std::vector<float> between;
		for (int c = 0; c < 3; c++) {
			between.push_back(cubeCentre[c] - (*sphere->getPos())[c]);
		}
		float distance = sqrt(pow(between[0], 2) + pow(between[1], 2) + pow(between[2], 2));

		// Distance between them <= r1 + r2
		// This is why we aprocimate to spheres. It makes collision calculation super fast.
		if (distance <= sqrt(3) * cubeSize / 2 + sphere->getRad()) {
			return true;
		}
		return false;
	}

	// Recursion part, only return false if they all return false
	for (int i = 0; i < 8; i++) {
		if (octree->getSubTree(i) != nullptr) {
			bool result = treeCollidesSphere(octree->getSubTree(i), sphere);
			if (result) return true;
		}
	}

	return false;
}


// Find the minimum sized octree cube that completely contains the given sphere
Octree* CollisionDetection::minEncompasingCube(Octree* octree, Sphere* sphere) {
	// Go through all sub-cubes
	for (int i = 0; i < 8; i++) {
		// Ensure this subtree exists
		if (octree->getSubTree(i) == nullptr) continue;

		// Oof yea I know this is a long line :/
		std::vector<float> subCentre = this->worldInterface->getNodeCoordinate(octree->getSubTree(i));
		float subSize = this->worldInterface->getNodeSize(octree->getSubTree(i));

		// TODO /* double check this since it's a bit complex and I'm tired */
		if (this->cubeContainsSphere(subCentre, subSize, sphere)) {
			if (octree->getSubTree(i) == nullptr) { 
				// If a sub-cube contains the sphere, but the octree ends before that, return
				// the parent tree
				return octree;
			} else if (!octree->getSubTree(i)->isSolid()) {
				// If a sub-cube contains the sphere, and is completely empty, return the
				// sub-tree
				return octree->getSubTree(i);
			}
			// Recursive solution to keep going smaller
			return this->minEncompasingCube(octree->getSubTree(i), sphere);
		}
	}
	return octree;
}

// Return true if the given sphere is completely within a cube with given centre and side length.
bool CollisionDetection::cubeContainsSphere(std::vector<float> centre, float length, Sphere* sphere) {
	for (int c = 0; c < 3; c++) {
		// If the negative side of the cube + the sphere radius is >= to sphere centre
		if ((centre[c] - 0.5 * length) + sphere->getRad() >= (*sphere->getPos())[c]) return false;
		// If the positive side of the cube - the sphere radius is <= to sphere centre
		if ((centre[c] + 0.5 * length) - sphere->getRad() <= (*sphere->getPos())[c]) return false;
	}

	return true;
}
