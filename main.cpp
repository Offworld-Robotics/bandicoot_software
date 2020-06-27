// Copyright blah blah UNSW Off World Robotics 2020

#include "RobotArm.h"
#include "Lever.h"
#include "Rotator.h"

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>

int main(int argc, const char** argv) {
    std::cout << "Program start" << std::endl;

    RobotArm armRep = RobotArm();
    Lever* l0 = new Lever(2, 0.1, 1, -3, 3);
    Rotator* r0 = new Rotator(0, 0.2, M_PI/2, -3, 3);
    Lever* l1 = new Lever(0.5, 0.1, 1, -3, 3);

    armRep.addSegment(l0);
    armRep.addSegment(r0);
    armRep.addSegment(l1);

    std::vector<float> pos = armRep.getSegmentPos(1);
    std::cout << "Position: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
    pos = armRep.getSegmentPos(2);
    std::cout << "Position: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
    pos = armRep.getSegmentPos(3);
    std::cout << "Position: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;

    return 0;
}