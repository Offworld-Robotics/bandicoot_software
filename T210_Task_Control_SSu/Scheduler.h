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

    // returns whether there a task at a wait queue's index exists
    bool isValidIndex(int index) {
        return !*waitQ.isEmpty() && index >= 0 && index < *waitQ.size();
    }
public: 
    Scheduler(Controller c) {
        controller = c;
        waitQ = new list<Task>;
    }

    // returns the task located at index in the wait queue
    Task getTask(int index) {
        if (!isValidIndex(index)) {
            return NULL;
        }

        list<Task>::iterator it = *waitQ.begin();
        advance(it, index);
        return *it;
    }
    
    // adds a task to the back of the wait queue
    // attempts to dispatch the task for execution when there 
    // are no other waiting tasks
    void addTask(Task task) {
        *waitQ.push_back(task);

        if (*waitQ.size() == 1) {
            dispatchTask();
        } else {
            *waitQ.push_back(task);
        }
    }

    // removes the task at the given index in the wait queue
    Task removeTask(int index) {
        Task t = getTask(index);

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

    // moves the task located at one index into another index in the wait queue
    void repositionTask(int oldIndex, int newIndex) {
        if (!isValidIndex(oldIndex) || !isValidIndex(newIndex)) {
            return;
        }

        Task t = getTask(oldIndex);
        *waitQ.remove(t);
        list<Task>::iterator it = *waitQ.begin();
        advance(it, newIndex);
        *waitQ.insert(it, t);
    }
};

#endif 
