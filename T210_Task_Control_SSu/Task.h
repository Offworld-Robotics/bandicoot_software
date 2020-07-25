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
    int currentActionIndex;
	bool areValidParameters(string params) {
		return true;
	}
public:
    Task() {
        currentActionIndex = 0;
    }
    bool input(string params) {
    	if (!areValidParameters(params)) {
    		return false;
    	}
    	
    	return true;
    }

    int getID(void) {
        return ID;
    }

    void execute(void) {
        actionList[currentActionIndex].execute();
    }
};

#endif 
