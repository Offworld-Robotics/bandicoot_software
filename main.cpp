// Maria Cuyutupa Garcia 2020
// T201

#include <iostream>
#include <list> 
#include <queue>

using namespace std;

class BaseMediator;
class Mediator {
    public:
        virtual void notify (BaseMediator *sender) = 0;
};

class BaseMediator {
    protected:
        Mediator *mediator;
    
    public:
        void set_mediator(Mediator *mediator) {

        }       
};

class Action {
    public:
        virtual void executeAction () = 0;

};

class Task {
    private:
        int priority;
        int status; 
        list <Action> actionList;

    protected:
        void setPriority (int priorityTask) {
            priority = priorityTask;
        }    

        void setStatus (int statusTask) {
            status = statusTask; 
        }

        //void addListAction (Action action)
};

class Queue {
    private:
    void checkPriorityTask (Task task) {

    }

    protected:
    queue <Task> queueTask;

    public:
        void enqueueTask (Task task) {

        }
        
        Task dequeueTask (Task task) {
        
        }

};

class Scheduler : public BaseMediator{
    private:
        Queue Ready;
        Queue Blocked;

    public:
        bool isResourceAvailable () {
            return true;
        }

        void updateResources () {

        }

        void updateQueue (Queue queue) {

        }

        bool checkTask (Task task) {
           return true;
        }

        void addTask (Task task) {

        }

        void blockTask (Task task) {

        }

        void removeTask (Task task) {

        }

};

class Dispatcher {
    private:
        bool isEmpty (Queue readyQueue) {
            return true;
        }

        void activateExecuter () {

        }

};

class Executer {
    private:
        list <Task> runningTasks;

    public:
        void cancelTask (Task task) {

        }

        void runTask (Task task) {

        }
};

class TaskGenerator : public BaseMediator{
    public:
        Task createTask (char* command) {
        
        }

        bool validateTask (Task task) {
            return true;
        }

        Task getTask (Task task) {

        }

};

class InputInterpreter : public BaseMediator{


};

class ErrorHandler {
    protected:
    char* data;

    public:
        void handleError () {

        }

        void messageError () {

        }
};

class ConcreteMediator : public BaseMediator {
    private:
        Scheduler *scheduler;
        TaskGenerator *taskGenerator;
        InputInterpreter *inputInterpreter;
    
    public:
        ConcreteMediator(Scheduler *c1, TaskGenerator *c2) : scheduler(c1), taskGenerator(c2) {

        }

        ConcreteMediator(InputInterpreter *c1, TaskGenerator *c2) : inputInterpreter(c1), taskGenerator(c2) {

        }
        void getNextInput () {

        }
        void sendCommandDescription () {

        }
        void getTask () {

        }
        void addTask () {

        }

};

int main (void) {
    return 0;
}