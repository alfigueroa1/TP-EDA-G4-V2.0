#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        VALUE FSM
 ************************************************************/
class FSMValue :public genericFSM {

public:
	FSMValue() {
		rowCount = 8;
		done = false;
		state = valueState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case '"':
			return 1;
		case '-': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			return 2;
		case '{':
			return 3;
		case '[':
			return 4;
		case 't':
			return 5;
		case 'f':
			return 6;
		case 'n':
			return 7;
		default:
			return 8;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case valueState0:	j = 0; break;
		case NEWSTRING:		j = 1; break;
		case NEWNUM:		j = 2; break;
		case NEWOBJ:		j = 3; break;
		case NEWARRAY:		j = 4; break;
		case NEWTRUE:		j = 5; break;
		case NEWFALSE:		j = 6; break;
		case NEWNULL:		j = 7; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(state * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMValue::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[64] = {
		//Recibir '"'				Recibir '-' o 0-9		Recibir '{'				Recibir '['					Recibir 't'						Recibir 'f'						Recibir 'n'				Recibir otro
		{NEWSTRING, QX(valueOk)},	{NEWNUM, QX(valueOk)},	{NEWOBJ, QX(valueOk)},	{NEWARRAY, QX(valueOk)},	{NEWTRUE, QX(valueOk)},			{NEWFALSE, QX(valueOk)},		{NEWNULL, QX(valueOk)},	{ERROR, QX(valueNop)},	//INIT
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWSTRING	
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWNUM
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWOBJ
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWARRAY
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWTRUE
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWFALSE
		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		{FIN, QX(valueOk)},			{FIN, QX(valueOk)},				{FIN, QX(valueOk)},				{FIN, QX(valueOk)},		{FIN, QX(valueOk)},		//NEWNULL
	};
	void valueNop(eventType* ev) {
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};