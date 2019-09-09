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
		rowCount = 6;
		done = false;
		state = falseState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case 'f':
			return 1;
		case 'a':
			return 2;
		case 'l':
			return 3;
		case 's':
			return 4;
		case 'e':
			return 5;
		default:
			return 6;
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
		case falseState4:	j = 4; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMFalse::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[30] = {
		//Recibir 'f'					Recibir 'a'						Recibir 'l'						Recibir 's'						Recibir 'e'				Recibir others
		{falseState1, QX(valueNop)},	{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop) },			{falseState2, QX(valueNop)},	{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{falseState3, QX(valueNop)},	{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{falseState4, QX(valueNop)},	{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{ERROR, QX(valueNop)},			{FIN, QX(valueNop)},	{ERROR, QX(valueNop)}
	};
	void valueNop(eventType* ev) {
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};