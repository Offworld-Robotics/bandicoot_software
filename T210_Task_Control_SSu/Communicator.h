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
	void handleScheduler(String message);
	void handleExecutor(String message);
	void handleGenerator(String message);
	void handleInputInterpreter(String message);
	void handleFeedbackResolver(String message);
public:
	Communicator(void) {
		return;
	}
	void notify(message) {
		return;
	}
}; 
