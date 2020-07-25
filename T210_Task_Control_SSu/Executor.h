#include <iostream>
#include <list>
#include <unordered_map>
#include "Controller.h"
#include "Task.h"

#ifndef EXECUTOR_H
#define EXECUTOR_H

class Executor {
private:
	Controller controller;
    unordered_map<int, bool> resourceTable;
    vector<Task> executingList;
    list<Task> blockQ;
    bool isRunning;
    
    void executeTask(Task task) {
        task.execute();
    }
    
    void finishTask(Task task) {
        freeResources(task);
        for (auto it = v.begin(); it != v.end(); ++it) {
            if (*it == task){
                v.erase(it);
                return;
            }
        }
    }

    void freeResources(Task task) {
        vector<int> actuatorIDs = task.getActuatorIDs();
        for (auto &ID : actuatorIDs) {
            resourceTable[ID] = false;
        }
    }

public:
    Executor(Controller c) {
        controller = c;
        isRunning = false;
        blockQ = new list<Task>;

    }
    
    void run(void) {
        running = true;

    }
    
    void stop(void) {
        running = false;
    }
    
    bool canExecuteTask(Task task) {
        if (!isRunning) {
            return false;
        }

        vector<int> actuatorIDs = task.getActuatorIDs();
        for (auto &ID : actuatorIDs) {
            if (resourceTable.at(ID)) {
                return false;
            }
        }

        return true;
    }

    Task getBlockedTask(int taskID) {
        if (*blockQ.isEmpty()) {
            return NULL;
        }
        
        for (auto it = *blockQ.begin(); it != *blockQ.end(); ++it) {
            auto currTask = *it;
            if (currTask.getID() == taskID) {
                return currTask;
            }
        }

        return NULL;
    }

    void removeBlockedTask(Task task) {
        if (task != NULL) {
            *blockQ.remove(task);
        }
    }

    // adds a task to the executing queue
    void addTask(Task task) {
        if (canExecuteTask(task)) {
            executingList.push_back(task);
        }
    }

    Task removeRunningTask(int taskID) {
        for (auto it = executingList.begin(); it != executingList.end(); ++it) {
            if (*it.getID() == taskID) {
                executingList.erase(it);
                return;
            }
        }

        return NULL;
    }


    void blockTask(int taskID) {
        Task t = removeRunningTask(taskID);
        if (t == NULL) {
            return;
        }

        *blockQ.push_back(t);
    }

    void unblockTask(int taskID) {
        Task t = getBlockedTask(taskID);
        if (t == NULL) {
            return;
        }

        if (canExecuteTask(t)) {
            removeBlockedTask(t);
            addTask(t);
        }
    }

    bool isCurrentlyRunning(void) {
        return isRunning;
    }
};

#endif 
