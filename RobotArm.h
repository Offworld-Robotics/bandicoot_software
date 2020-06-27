#pragma once

#include "Segment.h"

#include <vector>

class RobotArm {
public:
    RobotArm();

    int getNSegments();

    void addSegment(Segment*);

    std::vector<float> getSegmentPos(int);

    CollisionObject getSegmentCollision(int);
    float getCollisionPrecision();

    bool setSegmentRot(int, float);

    void generateCollision(float);

private:
    int nSegments = 0;
    std::vector<Segment*> segments;
    float collisionPrecision = 0;
};