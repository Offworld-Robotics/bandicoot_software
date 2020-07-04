#include <iostream>
#include <unordered_map>
#include <tasks.>
#include "Communicator.h"

#ifndef INPUT_H
#define INPUT_H

class InputInterpreter { 
private:
	Communicator communicator;
	unordered_map<string, vector<string>> inputTable;
	bool areValidParameters(string params) {
		return true;
	}
public: 
    InputInterpreter(Communicator c) {
        this.communicator = c;
    }
    bool input(string params) {
    	if (!areValidParameters(params)) {
    		return false;
    	}
    	
        communicator.notify("InputInterpreter" + params);

    	return true;
    }
};

#endif 
