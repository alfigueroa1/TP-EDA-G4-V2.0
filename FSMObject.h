#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        OBJECT FSM
 ************************************************************/
class FSMObject :public genericFSM {

public:
	FSMObject() {
		rowCount = 5;
		done = false;
		state = objectState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case '"':
			return 1;
		case '}':
			return 2;
		case ':':
			return 3;
		case ',':
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
		case objectState0:	j = 0; break;
		case NEWSTRING:		j = 1; break;
		case objectState1:	j = 2; break;
		case NEWVALUE:		j = 3; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:
#define RX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMObject::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[20] = {
		//'"'							"}"					":"								","				OTHER
		{NEWSTRING, RX(nopObj)},	{FIN,RX(objectOk)},	{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},	//objectState0
		{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},	{objectState1, RX(nopObj)},	{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},	//NEWSTRING
		{NEWVALUE,RX(nopObj)},		{ERROR,RX(nopObj)},	{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},	//objectState1
		{ERROR,RX(nopObj)},			{FIN,RX(objectOk)},	{ERROR,RX(nopObj)},			{NEWSTRING},			{ERROR,RX(nopObj)},	//NEWVALUE		
	};
	void nopObj(eventType* ev) {
		return;
	}
	void objectOk(eventType* ev) {
		done = true;
	}
	
};
