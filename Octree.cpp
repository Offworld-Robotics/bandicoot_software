#include "Octree.h"



Octree::Octree(int depth) {
	this->depth = depth;
}

Octree::~Octree() {
	delete[] this->subTrees;
}

int Octree::getDepth() {
	return this->depth;
}

Octree* Octree::getSubTree(int index) {
	return this->subTrees[index];
}

void Octree::setEmpty(int index, Octree* tree) {
	this->solid = false;
	this->subTrees[index] = tree;
}

bool Octree::isSolid() {
	return this->solid;
}
