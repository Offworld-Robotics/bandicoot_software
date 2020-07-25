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
    // linked list of tasks, ordered by priority, where the highest
    // priority task is at the front of the linked list
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
            return;
        }

        auto it = *readyQ.begin()
        for (; it != *readyQ.end(); ++it) {
            auto currTask = *it;
            if (currTask.getPriority() < task.getPriority()) {
                break;
            }
        }

        *readyQ.emplace(it, task);
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
    
    // dispatches as many tasks as possible
    void maximumDispatchTask(void) {
        while (dispatchTask());
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
