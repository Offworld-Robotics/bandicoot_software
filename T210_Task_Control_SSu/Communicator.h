#include <iostream>
#include <stdlib.h> 
#include <map>

#include "Scheduler.h"
#include "Executor.h"
#include "Generator.h"
#include "InputInterpreter.h"
#include "FeedbackResolver.h"

class Communicator {
private:
	Scheduler scheduler;
	Executor executor;
	Generator generator;
	InputInterpreter inputInterpreter;
	FeedbackResolver feedbackResolver;

	void handleScheduler(string message) {

	}

	void handleExecutor(string message) {
		
	}

	void handleGenerator(string message) {

	}

	void handleInputInterpreter(string message) {

	}

	void handleFeedbackResolver(string message) {

	}


public:
	Communicator(void) {
		this.scheduler = new Scheduler();
		this.executor = new Executor();
		this.generator = new Generator();
		this.inputInterpreter = new InputInterpreter();
		this.feedbackResolver = new FeedbackResolver();
	}
	void notify(message) {
		char *first = strtok(message, " ");
		size_t spacePos = message.find(" ");
		string msg = message.substr(spacePos + 1);
		if (first == "Scheduler") {
			handleScheduler(msg);
		} else if (first == "Executor") {
			handleExecutor(msg);
		} else if (first == "Generator") {
			handleGenerator(msg);
		} else if (first == "InputInterpreter") {
			handleInputInterpreter(msg);
		} else if (first == "FeedbackResolver") {
			handleFeedbackResolver(msg);
		} else {
			return;
		}
	}
}; 
