#include <iostream>

#ifndef ACT_H

#include "Action/MotionAction.h"
#include "Action/SensorAction.h"

#endif

#ifndef TASK_H
#define TASK_H

class Task { 
private:
    vector<Action> actionList;
	double priority;
    int ID;
	int state;
    int currentActionID;
	bool areValidParameters(string params) {
		return true;
	}
public:
    Task() {
        return;
    }
    bool input(string params) {
    	if (!areValidParameters(params)) {
    		return false;
    	}
    	
    	return true;
    }
};

#endif 
