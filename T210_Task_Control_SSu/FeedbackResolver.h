#include <iostream>
#include <unordered_map>
#include "Communicator.h"

#ifndef ACT_H

#include "Action/MotionAction.h"
#include "Action/SensorAction.h"

#endif

#ifndef FEEDBACK_H
#define FEEDBACK_H

class FeedbackResolver { 
private:
	Communicator communicator;
public: 
	FeedbackResolver() {
		return;
	}
    void feedback(Action action, string feedbackData) {
        return;
    }
};

#endif 
