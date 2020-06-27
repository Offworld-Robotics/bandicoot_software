#include <iostream>
#include <list>
#include "Communicator.h"
#include "Task.h"

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
private:
	Communicator communicator;
	list<Task> readyQ;
public: 
    void addTask(Task task) {
        return;
    }
    Task removeTask(int taskID) {
        return NULL;
    }
    bool dispatchTask(void) {
        return true;
    }
    void maximumDispatchTask(void) {
        return;
    }
    Task popTask(void) {
    	return NULL;
    }
    Task getTask(int taskID) {
    	return NULL;
    }
};

#endif 
