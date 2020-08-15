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
	list<Task> *waitQ;
public: 
    Scheduler(Controller c) {
        controller = c;
        waitQ = new list<Task>;
    }

    Task getTask(int taskID) {
        if (*waitQ.isEmpty()) {
            return NULL;
        }

        for (auto task : *waitQ) {
            if (task.getID() == taskID) {
                return task;
            }
        }

        return NULL;
    }
    
    void addTask(Task task) {
        if (*waitQ.isEmpty()) {
            *waitQ.push_front(task);
            dispatchTask();
            return;
        }

        *waitQ.push_back(task);
    }

    Task removeTask(int taskID) {
        Task t = getTask(taskID);
        
        if (t != NULL) {
            *waitQ.remove(t);
        }

        return t;
    }
    
    // sends the task at the front of the ready queue to run in the executor
    // returns whether a task was dispatched or not
    bool dispatchTask(void) {
        Task t = *waitQ.front();
        if (t != NULL && controller.executor.canExecuteTask(t)) {
            controller.executor.addTask(t);
            *waitQ.pop_front();
            return true;
        } else {
            return false;
        }
    }
    
    Task popTask(void) {
    	if (*waitQ.isEmpty()) {
            return NULL;
        }

        Task t = *waitQ.front();
        *waitQ.pop_front();
        return t;
    }
};

#endif 
