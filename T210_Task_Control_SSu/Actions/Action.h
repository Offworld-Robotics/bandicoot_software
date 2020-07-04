#ifndef ACT_H 
#define ACT_H 

class Action { 
    public: 
        virtual void execute() = 0;
        virtual void pause() = 0; 
        virtual int getResourceID() = 0;
};  

#endif 
