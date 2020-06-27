#pragma once

#include "CollisionObject.h"

#include <vector>

class Segment {
public:
    Segment(float, float, float);
    Segment(float, float, float, float, float);

    float getLength();
    float getThickness();
    float getCurrentRot();

    bool setCurrentRot(float);

    // Input are 2 normalised 3d vectors, one in the tangent direction of the arm,
    // and another in the perpendicular direction to the tangent and direction
    // of the arm. The first represents where the arm is actually pointed, and
    // the second represents its rotation (ie. rotate first around the second one
    // for a lever if that makes sense). See Lever.cpp for more info on output.
    virtual void calculateEndDirection(std::vector<float>*) = 0;

    virtual void generateCollision(std::vector<float>, std::vector<float>, float) = 0;

    CollisionObject getCollision();

private:
    float length;
    float thickness;

    // Rotation starts from the centre with positive/negative radian values
    float currentRot = 0;

    // Zero will be assumed to mean infinte rotation.
    // If you do require no rotation in one direction, set it to something
    // small like 0.0001.
    float maxRot = 0;
    float minRot = 0;

protected:
    CollisionObject segCollision;
};