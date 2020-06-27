#include <iostream> 

#ifndef ACT_H

#include "Action.h" 

#endif 

#ifndef SENSOR_H
#define SENSOR_H

class SensorAction : public Action { 
    public: 
    	SensorAction() {
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
