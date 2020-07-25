#ifndef ACT_H 
#define ACT_H 

class Action { 
protected:
	int id;
public: 
    virtual void execute() = 0;
    virtual void pause() = 0; 
    virtual int getResourceID() = 0;
    virtual vector<int> getActuatorIDs() = 0;
};

#endif 
