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
    void createTask(string params) {
        
    }
};

#endif 
