#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        ARRAY FSM
 ************************************************************/
class FSMArray :public genericFSM {

public:
	FSMArray(){
		rowCount = 4;
		done = false;
		state = arrayState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case '[':
			return 1;
		case ']':
			return 2;
		case ',':
			return 3;
		default:
			return 4;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case arrayState0:	j = 0; break;
		case arrayState1:	j = 1; break;
		case NEWSTRING:		j = 2; break;
		}
		state = FSMTable[(state * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:

#define AX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMArray::x))

	//const fsmCell FSMTable[2][3] = {
	const fsmCell FSMTable[12] = {
		//Recibir '['					RECIBIR ']'					//RECIBIR ','				//Other
		{arrayState1, AX(arrayError)},	{ERROR, AX(arrayError)},	{ERROR, AX(arrayError)},	{ERROR, AX(arrayError)},//arrayState0
		{NEWVALUE, AX(arrayOk)},		{NEWVALUE, AX(arrayOk)},	{NEWVALUE, AX(arrayOk)},	{NEWVALUE, AX(arrayOk)},//arraySate1
		{ERROR, AX(arrayError)},		{FIN, AX(arrayOk)},			{NEWVALUE, AX(arrayOk)},	{ERROR, AX(arrayError)}	//NEWVALUE
	};

	void arrayError(eventType* ev) {
		state = ERROR;
	}
	void arrayOk(eventType* ev) {
		return;
	}
};