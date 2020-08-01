#include "Task.h"

#ifndef ACT_H 
#define ACT_H 

class Action { 
protected:
	vector<int> actuatorIDs;
	Task task;
public: 
	virtual void Action(Executor);
    virtual void execute() = 0;
    virtual void pause() = 0; 
    virtual vector<int> getActuatorIDs() = 0;
    virtual void completeAction() = 0;
};

#endif 
