
#ifndef GENERICFSM_H
#define GENERICFSM_H

#include "events.h"

typedef unsigned int stateTypes;
//typedef unsigned int eventType;

class genericFSM;

struct fsmCell{
    stateTypes nextState;
    void (genericFSM::*action)(eventType*);
};


class genericFSM{
public:
    //void cycle(eventType* ev);
	virtual void cycle(eventType* ev) = 0;
	stateTypes getState() {
		return state;
	}
	bool getDone() {
		return done;
	}
    //char* getErrorCode();
	virtual int filterEvents(eventType) = 0;
protected:    
	stateTypes state;
    unsigned int rowCount;
	bool done;
private:
    unsigned int columnCount;
    fsmCell * FSMTAble; 
};

#endif /* GENERICFSM_H */

