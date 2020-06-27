#include <iostream>
#include <unordered_map>
#include "Communicator.h"
#include "Task.h"

#ifndef GENERATOR_H
#define GENERATOR_H

class Generator { 
private:
	Communicator communicator;
	unordered_map<int, Task> taskTable;
	bool areValidParameters(string params) {
		return true;
	}
public: 
	Generator() {
		return;
	}
    Task createTask(int ID, string params) {
        return NULL;
    }
};

#endif 
