#include <iostream> 

#ifndef ACT_H

#include "Action.h" 

#endif 

#ifndef MOTION_H
#define MOTION_H

class MotionAction : public Action {
    public:
    	MotionAction() {
    		return;
    	}
        void execute(void) {
        	return;
        }
        void pause(void) {
        	return;
        }
};

#endif 
