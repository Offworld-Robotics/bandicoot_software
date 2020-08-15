#include <iostream>
#include <list>
#include <unordered_map>
#include "Controller.h"
#include "Task.h"
#include "Action.h"

#ifndef EXECUTOR_H
#define EXECUTOR_H

class Executor {
private:
	Controller controller;
    Task executingTask;
    Task blockedTask;
    Action currentAction;
    bool isRunning;
    
    void executeTask() {
        if (canExecuteTask()) {
            executingTask.execute();
        }
    }
    
    void finishTask(Task task) {
        executingTask = NULL;
        controller.scheduler.dispatchTask();
    }

public:
    Executor(Controller c) {
        controller = c;
        isRunning = false;
    }
    
    void run(void) {
        running = true;
        controller.scheduler.dispatchTask();
        executeTask();
    }
    
    void stop(void) {
        running = false;
        executingTask.pause();
    }
    
    bool canExecuteTask(Task task) {
        return isRunning && executingTask == NULL;
    }

    void removeBlockedTask(Task task) {
        if (task != NULL) {
            *blockQ.remove(task);
        }
    }

    void addTask(Task task) {
        if (this.canExecuteTask()) {
            this.executingTask = task;
            executeTask();
        }
    }

    void blockTask(void) {
        if (executingTask != NULL) {
            blockedTask = executingTask;
            currentAction.pause();
            executingTask = NULL;
        }
    }

    void unblockTask(void) {
        Task t = blockedTask;
        if (t == NULL) {
            return;
        }

        if (canExecuteTask(t)) {
            addTask(t);
        } else {
            controller.scheduler.addTask(t);
        }

        blockedTask = NULL;
    }

    bool isCurrentlyRunning(void) {
        return isRunning;
    }
};

#endif 
