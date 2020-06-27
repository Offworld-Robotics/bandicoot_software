#pragma once

class Octree {
public:
	Octree(int);
	~Octree();

	int getDepth();
	Octree* getSubTree(int);

	void setEmpty(int, Octree*);

	bool isSolid();

private:
	int depth;
	bool solid = true;
	Octree* subTrees[8] = {nullptr};
};

