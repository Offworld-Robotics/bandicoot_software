#pragma once

#include "Octree.h"

class SLAMInterface {
public:
	void updateOctree() {
		// Nothing to do here since there is no SLAM.

		// This would update the octree pointer with the latest data.

		// This would be called when the MCL gets an instruction,
		// it will get the latest world data and have it be fixed while
		// it calculates stuff, since if the octree changes unexpectedly
		// in the middle of path planning it could cause issues.
	}

	Octree* getOctree() {
		return this->octree;
	}

	float getOctreeSize() {
		return this->octreeSize;
	}

	// This function needs to return the absolute 3d coordinates
	// of the centre of a given octree node
	std::vector<float> getNodeCoordinate(Octree* node) {
		return { 0, 0, 0 };
	}

	// Returns the size of the given octree. This placeholder code should
	// work fairly well for now
	float getNodeSize(Octree* node) {
		return this->octreeSize / pow(2, node->getDepth);
	}

	// Returns true if there are no sub-nodes smaller than this
	bool isEndNode(Octree* node) {
		for (int i = 0; i < 8; i++) {
			if (node->getSubTree(i) != nullptr) return false;
		}
		return true;
	}


	// temorary function for testing while this is a fake interface
	void setOctree(Octree* tree, float size) {
		delete this->octree;
		this->octree = tree;
		this->octreeSize = size;
	}

private:
	Octree* octree;
	float octreeSize;
};

