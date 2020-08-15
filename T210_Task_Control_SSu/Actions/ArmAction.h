#include <iostream> 

#ifndef ACT_H

#include "Action.h" 

#endif 

#ifndef ARM_H
#define ARM_H

class ArmAction : public Action { 
private:
    double destX;
    double destY;
    double destZ;
public: 
	ArmAction(double x, double y, double z) {
		this.destX = x;
        this.destY = y;
        this.destZ = z;
	}
    void execute(void) {
    	return;
    }
    void pause(void) {
    	return;
    }
};

#endif 
