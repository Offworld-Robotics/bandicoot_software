#include <iostream>
#include <list>
#include "Controller.h"
#include "Task.h"

using namespace std;

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
private:
	Controller controller;
    // linked list of tasks, where the front of the linked list
    // has the task that is next in line to be executed
	list<Task> *readyQ;
public: 
    Scheduler(Controller c) {
        controller = c;
        readyQ = new list<Task>;
    }

    Task getTask(int taskID) {
        if (*readyQ.isEmpty()) {
            return NULL;
        }
        
        for (auto it = *readyQ.begin(); it != *readyQ.end(); ++it) {
            auto currTask = *it;
            if (currTask.getID() == taskID) {
                return currTask;
            }
        }

        return NULL;
    }
    
    void addTask(Task task) {
        if (*readyQ.isEmpty()) {
            *readyQ.push_front(task);
            dispatchTask();
            return;
        }

        *readyQ.push_back(task);
    }

    Task removeTask(int taskID) {
        Task t = getTask(taskID);
        
        if (t != NULL) {
            *readyQ.remove(t);
        }

        return t;
    }
    
    // sends the task at the front of the ready queue to run in the executor
    // returns whether a task was dispatched or not
    bool dispatchTask(void) {
        Task t = popTask();
        if (t != NULL && controller.executor.canExecuteTask(t)) {
            controller.executor.addTask(t);
            return true;
        } else {
            addTask(t);
            return false;
        }
    }
    
    Task popTask(void) {
    	if (*readyQ.isEmpty()) {
            return NULL;
        }

        Task t = *readyQ.front();
        *readyQ.pop_front();
        return t;
    }
};

#endif 
