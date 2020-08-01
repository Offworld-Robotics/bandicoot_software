#include <iostream> 

#ifndef ACT_H

#include "Action.h" 

#endif 

#ifndef ARM_H
#define ARM_H

class ArmAction : public Action { 
    public: 
    	ArmAction() {
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
