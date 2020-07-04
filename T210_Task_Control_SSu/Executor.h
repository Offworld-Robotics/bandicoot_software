#include <iostream>
#include <list>
#include <unordered_map>
#include "Communicator.h"
#include "Task.h"

#ifndef EXECUTOR_H
#define EXECUTOR_H

class Executor {
private:
	Communicator communicator;
	list<Task> blockQ;
    unordered_map<int, bool> resourceTable;
    vector<Task> executingList;
    
    void executeTask(int taskID) {
        return;
    }
    
    void finishTask(int taskID) {
        this.communicator.notify("Executor Scheduler maximumTaskDispatch");
    }

    void freeResources(int taskID) {

    }
public:
    Executor(Communicator c) {
        this.communicator = c;
    }
    void run(void) {
        return;
    }
    void stop(void) {
        return;
    }
    bool canExecuteTask(Task task) {
        return true;
    }
    void addTask(Task task) {
        return;
    }
    Task removeTask(int taskID) {
        return NULL;
    }
    void blockTask(int taskID) {
        return;
    }
    void unblockTask(int taskID) {
        return;
    }
    bool isRunning(void) {
        return true;
    }
};

#endif 
