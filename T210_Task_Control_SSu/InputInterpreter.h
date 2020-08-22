#include <iostream>
#include <unordered_map>

#include "Controller.h"

#ifndef INPUT_H
#define INPUT_H

class InputInterpreter { 
private:
	Controller controller;
public: 
    InputInterpreter(Controller c) {
        this.controller = c;
    }
    void input(void) {
    	string params;
    	cin >> params;
        controller.handleInput(params);
    }
};

#endif 
