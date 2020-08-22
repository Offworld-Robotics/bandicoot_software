#include <iostream>

#include "Controller.h"

using namespace std;

int main(void) {
	Controller c = new Controller;
    while (true) {
    	Controller.inputInterpreter.input();
    }
    return 0;
}