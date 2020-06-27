#include "Segment.h"
#include "Segment.h"

Segment::Segment(float len, float thicc, float startRot) {
    this->length = len;
    this->thickness = thicc;
    this->currentRot = startRot;
}

Segment::Segment(float len, float thicc, float startRot, float min, float max) {
    this->length = len;
    this->thickness = thicc;
    this->currentRot = startRot;
    this->minRot = min;
    this->maxRot = max;
}

float Segment::getLength() {
    return this->length;
}

float Segment::getThickness() {
    return this->thickness;
}

float Segment::getCurrentRot() {
    return this->currentRot;
}

// Set current rotation while ensuring it's within rotation limits
bool Segment::setCurrentRot(float rot) {
    if ((this->minRot != 0 && rot >= this->minRot)
        && (this->maxRot != 0 && rot <= this->maxRot)) {

        this->currentRot = rot;
        return true;
    }

    return false;
}

CollisionObject Segment::getCollision() {
	return this->segCollision;
}
