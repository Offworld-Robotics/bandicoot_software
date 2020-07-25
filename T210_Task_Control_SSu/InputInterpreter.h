#include <iostream>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

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
    vector<string> input(string params) {
        vector<string> result;
    	boost::split(results, params, [](char c){return c == ' ';});
        return result;
    }
};

#endif 
