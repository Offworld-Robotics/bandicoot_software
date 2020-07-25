#include <iostream>
#include <unordered_map>
#include "Controller.h"
#include "Task.h"

#ifndef GENERATOR_H
#define GENERATOR_H

class Generator { 
private:
	Controller controller;
	// todo: define task table
	unordered_map<int, Task> taskTable;

	bool areValidParameters(string params) {
		return true;
	}
public: 
	Generator(Controller c) {
        this.controller = c;
    }
    
    Task createTask(int ID, string params) {
        return NULL;
    }
};

#endif 
