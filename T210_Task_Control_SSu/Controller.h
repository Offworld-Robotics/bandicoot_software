#include <iostream>
#include <stdlib.h> 
#include <map>

#include "Scheduler.h"
#include "Executor.h"
#include "Generator.h"
#include "InputInterpreter.h"


class Controller {
private:
	Scheduler scheduler;
	Executor executor;
	Generator generator;
	InputInterpreter inputInterpreter;
public:
	Controller(void) {
		this.scheduler = new Scheduler();
		this.executor = new Executor();
		this.generator = new Generator();
		this.inputInterpreter = new InputInterpreter();
	}

	void handleInput(vector<string> params) {
		
	}
}; 
