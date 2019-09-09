#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        FALSE FSM
 ************************************************************/
class FSMFalse :public genericFSM {

public:
	FSMFalse() {
		rowCount = 5;
		done = false;
		state = falseState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case 'a':
			return 1;
		case 'l':
			return 2;
		case 's':
			return 3;
		case 'e':
			return 4;
		default:
			return 5;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case falseState0:	j = 0; break;
		case falseState1:	j = 1; break;
		case falseState2:	j = 2; break;
		case falseState3:   j = 3; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMFalse::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[20] = {
		//Recibir 'a'					Recibir 'l'						Recibir 's'						Recibir 'e'					Recibir 'others'		
		{falseState1, QX(valueNop)},	{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop) },			{falseState2, QX(valueNop)},	{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{falseState3, QX(valueNop)},	{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{FIN, QX(valueNop)},		{ERROR, QX(valueNop)}
	};
	void valueNop(eventType* ev) {
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};