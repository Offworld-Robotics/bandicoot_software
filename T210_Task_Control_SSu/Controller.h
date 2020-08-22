#include <iostream>
#include <stdlib.h> 
#include <map>
#include <vector>

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

	void handleInput(string params) {
		// delegate request to correct subcomponents
		// what am I doing with my life
	}
}; 
