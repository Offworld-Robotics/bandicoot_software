#include <iostream> 

#ifndef ACT_H

#include "Action.h" 

#endif 

#ifndef MOTION_H
#define MOTION_H

class MotionAction : public Action {
private:
    double destX;
    double destY;
public:
	MotionAction(double x, double y) {
        this.destX = x;
		this.destY = y;
	}
    void execute(void) {
    	return;
    }
    void pause(void) {
    	return;
    }
};

#endif 
