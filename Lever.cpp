#include "Lever.h"
#include "CollisionObject.h"

#include <math.h>
#include <iostream>

Lever::Lever(float len, float thicc, float startRot) : Segment(len, thicc, startRot) {}

Lever::Lever(float len, float thicc, float startRot, float min, float max) : Segment(len, thicc, startRot, min, max) {}

void Lever::calculateEndDirection(std::vector<float>* basis) {
    // Basis is 2 normalised 3d vectors, one in the tangent direction of the arm,
    // and another in the perpendicular direction to the tangent and direction
    // of the arm. The first represents where the arm is actually pointed, and
    // the second represents its rotation (ie. rotate first around the second one
    // for a lever if that makes sense).

    // Return value is the same, showing the direction and rotation after this
    // arm segment does its thing.

    std::vector<float> direction = basis[0];
    std::vector<float> rotation = basis[1];


    std::cout << "Dir: " << direction[0] << " " << direction[1] << " " << direction[2] << std::endl;

    // For those interested, we're using the Rodrigues' Rotation Formula to
    // rotate the 'direction' vector around 'rotation' vector axis by
    // 'currRotation' radians.
    // https://mathworld.wolfram.com/RodriguesRotationFormula.html
    // Here's the formula, more for my convenience than yours tbh
    /*          
    | cos(θ)+rot[0]^2*(1-cos(θ))                rot[0]*rot[1]*(1-cos(θ))-rot[2]*sin(θ)   rot[1]*sin(θ)+rot[0]*rot[2]*(1-cos(θ))  |   | dir[0] |
    | rot[2]*sin(θ)+rot[0]*rot[1]*(1-cos(θ))    cos(θ) + rot[1]^2*(1-cos(θ))             -rot[0]*sin(θ)+rot[1]*rot[2]*(1-cos(θ)) | * | dir[1] |
    | -rot[1]*sin(θ)+rot[0]*rot[2]*(1-cos(θ))   rot[0]*sin(θ)+rot[1]*rot[2]*(1-cos(θ))   cos(θ)+rot[2]^2*(1-cos(θ))              |   | dir[2] |
    */

    std::vector<float> result;

    // Setting up temporary variables to make things faster and a bit eaiser to read.
    float sin_ = sin(this->getCurrentRot());
    float cos_ = cos(this->getCurrentRot());
    float cos_min = 1 - cos_;
    float w_0 = rotation[0];
    float w_1 = rotation[1];
    float w_2 = rotation[2];

    result.push_back(direction[0] * (cos_ + w_0 * w_0 * cos_min)        + direction[1] * (w_0 * w_1 * cos_min - w_2 * sin_) + direction[2] * (w_1 * sin_ + w_0 * w_2 * cos_min));
    result.push_back(direction[0] * (w_2 * sin_ + w_0 * w_1 * cos_min)  + direction[1] * (cos_ + w_1 * w_1 * cos_min)       + direction[2] * (-w_0 * sin_ + w_1 * w_2 * cos_min));
    result.push_back(direction[0] * (-w_1 * sin_ + w_0 * w_2 * cos_min) + direction[1] * (w_0 * sin_ + w_1 * w_2 * cos_min) + direction[2] * (cos_ + w_2 * w_2 * cos_min));

    std::cout << "Res: " << result[0] << " " << result[1] << " " << result[2] << std::endl;

    basis[0] = result;

    // Debug check making sure final 'direction' and 'rotation' are perpendicular.
    float dot = result[0] * w_0 + result[1] * w_1 + result[2] * w_2;
    if (fabs(dot - 0) < FLT_EPSILON) {
        std::cout << "lever output good" << std::endl;
    } else {
        std::cout << "lever output bad" << dot << std::endl;
    }
}

void Lever::generateCollision(std::vector<float> start, std::vector<float> end, float precision) {
    this->segCollision = CollisionObject();

    // 'Ceil' of how many times precision fits into the length of this segment
    int nSpheres = (this->getLength() / precision) + 1;

    // Distance between spheres along the arm
    float distance = this->getLength() / nSpheres;

    // Calculate the minimum radius for spheres to fully encompass the arm (simple pythag)
    float radius = 0.5 * sqrt(distance * distance + this->getThickness() * this->getThickness());

    // Create a vector representing the distance and direction between 2 adjacent spheres
    std::vector<float> between = { 0, 0, 0 };
    if (this->getLength() != 0) {
        for (int c = 0; c < 3; c++) {
            // Normalise then multiply by distance between spheres
            between.push_back((end[c] - start[c]) / this->getLength() * distance);
        }
    }

    for (int i = 0; i < nSpheres; i++) {
        // Calculate position of each sphere
        std::vector<float> spherePos;
        for (int j = 0; j < 3; j++) {
            spherePos.push_back(start[j] + between[j] * i);
        }

        this->segCollision.addSphere(spherePos, radius);
    }
}
