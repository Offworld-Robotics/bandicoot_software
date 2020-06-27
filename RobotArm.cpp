#include "RobotArm.h"

#include <iostream>

RobotArm::RobotArm() {
}

int RobotArm::getNSegments() {
    return this->nSegments;
}

void RobotArm::addSegment(Segment* s) {
    this->segments.push_back(s);
    this->nSegments++;
}

std::vector<float> RobotArm::getSegmentPos(int seg) {
    // Something bad :/
    if (seg > this->nSegments) throw "Segment number out of bounds";

    if (seg == 0) return { 0, 0, 0 };

    std::vector<float> basis[2];
    // x, y, z with z upwards and x straight ahead of rover
    // Position
    std::vector<float> position = { 0, 0, 0 };
    // Direction
    basis[0] = { 0, 0, 1 };
    // Rotation
    basis[1] = { 0, 1, 0 };

    for (int i = 0; i < seg; i++) {
        std::cout << "Position: " << basis[0][0] << " " << basis[0][1] << " " << basis[0][2] << std::endl;
        // Create deep copy (probably a better way to do this TODO).

        this->segments[i]->calculateEndDirection(basis);

        // Add the transormation to global position and normalise direction vector
        float length = sqrt(basis[0][0] * basis[0][0] + basis[0][1] * basis[0][1] + basis[0][2] * basis[0][2]);
        for (int j = 0; j < 3; j++) {
            // Scale result by length of arm segment then add it to global position
            position[j] += basis[0][j] * this->segments[i]->getLength();
            basis[0][j] = basis[0][j] / length;
        }
        std::cout << "" << std::endl;
    }

    // Return the position vector
    return position;
}

CollisionObject RobotArm::getSegmentCollision(int index) {
    return this->segments[index]->getCollision();
}

float RobotArm::getCollisionPrecision() {
    return this->collisionPrecision;
}

bool RobotArm::setSegmentRot(int index, float rot) {
    return this->segments[index]->setCurrentRot(rot);
}

void RobotArm::generateCollision(float precision) {
    this->collisionPrecision = precision;
    for (int s = 0; s < this->nSegments; s++) {
        this->segments[s]->generateCollision(this->getSegmentPos(s), this->getSegmentPos(s + 1), precision);
    }
}
