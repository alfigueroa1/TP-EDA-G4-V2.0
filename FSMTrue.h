#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        TRUE FSM
 ************************************************************/
class FSMTrue :public genericFSM {

public:
	FSMTrue() {
		rowCount = 4;
		done = false;
		state = trueState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case 'r':
			return 1;
		case 'u':
			return 2;
		case 'e':
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
		case trueState0:	j = 0; break;
		case trueState1:	j = 1; break;
		case trueState2:	j = 2; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMTrue::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[12] = {
		//Recibir 'r'				Recibir 'u'					Recibir 'e'				Recibir 'others'		
		{trueState1, QX(valueNop)},	{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop) },		{trueState2, QX(valueNop) }, {ERROR, QX(valueNop) }, {ERROR, QX(valueNop) },
		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{FIN, QX(valueNop)},		{ERROR, QX(valueNop)},
	};
	void valueNop(eventType* ev) {
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};