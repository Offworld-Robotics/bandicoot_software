#include "Task.h"

#ifndef ACT_H 
#define ACT_H 

class Action { 
protected:
	Task task;
public: 
	virtual void Action(Executor);
    virtual void execute() = 0;
    virtual void pause() = 0; 
};

#endif 
