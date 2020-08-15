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
    int ID;
	int state;
    int currentActionIndex;
    Executor executor;
public:
    Task(Executor executor) {
        this.executor = executor;
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

    void pause(void) {
        actionList[currentActionIndex].pause();
    }

    void completeAction(Action action) {
        currentActionIndex++;
        if (currentActionIndex == actionList.size()) {
            executor.finishTask(this);
        }
        execute();
    }
};

#endif 
