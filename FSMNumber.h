#ifndef _FSMNUMBER_H
#define _FSMNUMBER_H

#include "genericFSM.h"
#include "events.h"
#include "FSMstates.h"

class FSMNumber:public genericFSM{

public:
	FSMNumber() {
		rowCount = 8;
		done = false;
		state = numState0;
	}
	virtual int filterEvents(eventType ev) {
		switch (ev) {
		case '-':
			return 1;
		case '0':
			return 2;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			return 3;
		case '.':
			return 4;
		case 'e':
			return 5;
		case 'E':
			return 6;
		case '+':
			return 7;
		default: return 8;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case numState0:	j = 0; break;
		case numState1:	j = 1; break;
		case numState2:	j = 2; break;
		case numState3:	j = 3; break;
		case numState4:	j = 4; break;
		case numState5:	j = 5; break;
		case numState6:	j = 6; break;
		case numState7:	j = 7; break;
		case numState8:	j = 8; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(j * rowCount) + (evento - 1)].action;
	}

private:
#define TX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMNumber::x))

    const fsmCell FSMTable[72] = {

            // Recibir -				// Recibir 0				// Recibir digit			// Recibir .				// Recibir e				// Recibir E				// Recibir +                //Recibir fin
            {numState1, TX(nopNum)},	{numState2, TX(nopNum)},	{numState3, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{numState1, TX(nopNum)},   {ERROR, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState2, TX(nopNum)},	{numState3, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},       {ERROR, TX(nopNum)},
            {ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{numState4, TX(nopNum)},	{numState6, TX(nopNum)},	{numState6, TX(nopNum)},	{ERROR, TX(nopNum)},       {FIN, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState3, TX(nopNum)}, 	{numState3, TX(nopNum)},	{numState4, TX(nopNum)},	{numState6, TX(nopNum)},		{numState6, TX(nopNum)},		{ERROR, TX(nopNum)},       {FIN, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState5, TX(nopNum)},	{numState5, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},       {ERROR, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState5, TX(nopNum)},	{numState5, TX(nopNum)},	{ERROR, TX(nopNum)},		{numState6, TX(nopNum)},	{numState6, TX(nopNum)},	{ERROR, TX(nopNum)},       {FIN, TX(nopNum)},
            {numState7, TX(nopNum)},	{numState8, TX(nopNum)},	{numState8, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{numState7, TX(nopNum)},	{ERROR, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState8, TX(nopNum)},	{numState8, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},       {ERROR, TX(nopNum)},
            {ERROR, TX(nopNum)},		{numState8, TX(nopNum)},	{numState8, TX(nopNum)},	{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},		{ERROR, TX(nopNum)},       {FIN, TX(nopNum)},
    };
	void nopNum(eventType* ev) {
		return;
	}
	void numOk(eventType* ev) {
		done = true;
	}
};

#endif //_FSMNUMBER_H
