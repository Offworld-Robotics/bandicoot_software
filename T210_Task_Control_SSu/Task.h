#include <iostream>

#ifndef ACT_H

#include "Actions/MotionAction.h"
#include "Actions/SensorAction.h"

#endif

#ifndef TASK_H
#define TASK_H

class Task { 
private:
    vector<Action> actionList;
    int currentActionIndex;
public:
    Task() {
        currentActionIndex = 0;
    }

    void addAction(Action a) {
        actionList.push_back(a);
    }

    bool hasNext(void) {
        return currentActionIndex < actionList.size();
    }

    Action getNext(void) {
        if (!hasNext()) {
            return NULL;
        }
        return actionList[++currentActionIndex];
    }
};

#endif 
