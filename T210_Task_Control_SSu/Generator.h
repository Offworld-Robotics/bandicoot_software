#include <iostream>
#include <unordered_map>
#include "Controller.h"
#include "Task.h"

#ifndef GENERATOR_H
#define GENERATOR_H

class Generator { 
private:
	Controller controller;
public: 
	Generator(Controller c) {
        this.controller = c;
    }
    
    // move x y 
    void createTask(vector<string> params) {
        Task t = new Task();
        for (auto s : params) {
        	// parse
        	Action a = new MotionAction(0, 0/*params*/);
        	t.addAction(a);
        }
        controller.scheduler.addTask(t);
    }
};

#endif 
