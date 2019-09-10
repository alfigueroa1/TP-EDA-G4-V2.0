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
		rowCount = 6;
		done = false;
		state = objectState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case '{':
			return 1;
		case '"':
			return 2;
		case '}':
			return 3;
		case ':':
			return 4;
		case ',':
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
		case objectState0:	j = 0; break;
		case objectState1:	j = 1; break;
		case NEWSTRING:		j = 2; break;
		case objectState2:	j = 3; break;
		case NEWVALUE:		j = 4; break;
		case objectState3:	j = 5; break;
		case objectState4:  j = 6; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(j * rowCount) + (evento - 1)].action;
	}

private:
#define RX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMObject::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[42] = {
		//'{'						'"'						"}"						":"							","							OTHER
		{objectState1, RX(nopObj)},	{ERROR, RX(nopObj)},	{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},	//objectState0
		{ERROR, RX(nopObj)},		{NEWSTRING, RX(nopObj)},{objectState4,RX(objectOk)},		{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},	//objectState1
		{ERROR, RX(nopObj)},		{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},		{objectState2, RX(nopObj)},	{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},	//NEWSTRING
		{NEWVALUE, RX(nopObj)},		{NEWVALUE,RX(nopObj)},	{ERROR,RX(nopObj)},		{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},			{NEWVALUE,RX(nopObj)},	//objectState2
		{ERROR, RX(nopObj)},		{ERROR,RX(nopObj)},		{objectState4,RX(objectOk)},		{ERROR,RX(nopObj)},			{objectState3,RX(nopObj)},	{ERROR,RX(nopObj)},	//NEWVALUE		
		{ERROR, RX(nopObj)},		{NEWSTRING,RX(nopObj)},	{ERROR,RX(objectOk)},	{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},			{ERROR,RX(nopObj)},	//objectState3
		{FIN, RX(nopObj)},			{FIN,RX(nopObj)},		{FIN,RX(objectOk)},		{FIN,RX(nopObj)},			{FIN,RX(nopObj)},			{FIN,RX(nopObj)}
	};
	void nopObj(eventType* ev) {
		return;
	}
	void objectOk(eventType* ev) {
		done = true;
	}
	
};
