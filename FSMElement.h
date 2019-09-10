#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        OBJECT FSM
 ************************************************************/
class FSMElement :public genericFSM {

public:
	FSMElement() {
		rowCount = 0;
		done = true;
		state = elementState0;
	}
	virtual int filterEvents(eventType ev) {
		return 0;
	}
	virtual void cycle(eventType* ev) {
		state = FSMTable[0].nextState;
		FSMTable[0].action;
	}

private:
#define FX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMElement::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[1] = {
		//ANYTHING
		{NEWVALUE, FX(elementOk)}		
	};
	void elementOk(eventType* ev) {
		done = true;
		return;
	}

};
