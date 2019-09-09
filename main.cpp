#include <iostream>
#include <stdlib.h>
#include "events.h"
#include "genericFSM.h"
#include "FSMValue.h"
#include "FSMObject.h"
#include "FSMNumber.h"
#include "FSMString.h"
#include "FSMTrue.h"
#include "FSMFalse.h"
#include "FSMNull.h"

void stackFSMsPush(int instance, genericFSM** stack, uint &stackLevel);
void stackFSMsPop(genericFSM** stack, uint& stackLevel);
void freeStack(genericFSM** stack, uint& stackLevel);

int main(int argc, char** argv) {
	genericFSM* stackFSMs[100];
	FSMValue valor;
	int error = 0, quit = 0, line = 1;
	int instance  = 0;
	eventType ev = NOEVENT;
	FILE* archivo;
	stackFSMs[0] = &valor;
	archivo = fopen("JSONFile.txt", "r");
	if (archivo == NULL) {
		printf("Error al intentar abrir el archivo de Json\n");
		return 0;
	}
	unsigned int stackLevel = 0, last = 0;
	while (ev != EOF && !quit) {
		ev = getNextEvent(archivo, line);
		if (ev != NOEVENT) {
			printf("Event detected: %c at line %d\n", ev, line);
			stackFSMs[stackLevel]->cycle(&ev);
			while (stackFSMs[stackLevel]->getDone() == true) {
				if (stackLevel == 0) {
					break;
				}
				else {
					stackFSMsPop(stackFSMs, stackLevel); 
					printf("Instance finished, stack poped\n");
					printf("StackLevel: %d\n", stackLevel);
				}
				continue;
			}
			if ((stackFSMs[stackLevel]->getState()) == ERROR) {
				quit = 1;
				printf("Error Found at line %d!\n", line);
			}
			else if ((stackFSMs[stackLevel]->getState()) == FIN) {
				if (stackLevel == 0) {
					break;
				}
				else{
					stackFSMsPop(stackFSMs, stackLevel);
					printf("Instance finished, stack poped\n");
					printf("StackLevel: %d\n", stackLevel);
				}
			}
			else if ((stackFSMs[stackLevel]->getState()) == NEWOBJ || (stackFSMs[stackLevel]->getState()) == NEWARRAY
				|| (stackFSMs[stackLevel]->getState()) == NEWTRUE || (stackFSMs[stackLevel]->getState()) == NEWFALSE || (stackFSMs[stackLevel]->getState()) == NEWNULL
				|| (stackFSMs[stackLevel]->getState()) == NEWVALUE || (stackFSMs[stackLevel]->getState()) == NEWSTRING || (stackFSMs[stackLevel]->getState()) == NEWNUM) {
				stackFSMsPush(stackFSMs[stackLevel]->getState(), stackFSMs, stackLevel);
				last = stackLevel;
				printf("New FSM instance needed!\n");
				printf("StackLevel: %d\n", stackLevel);
			}
		}
	}
	freeStack(stackFSMs, stackLevel);
	if (quit) 
		printf("Invalid sintaxis in file\n");
	else
		printf("Valid File\n");
	fclose(archivo);
	return 0;
}



void stackFSMsPush(int instance, genericFSM** stack, uint& stackLevel) {
	genericFSM* newFSM = NULL;
	switch (instance) {
	case NEWOBJ:	newFSM = new (std::nothrow) FSMObject;	printf("Entering Object FSM\n"); break;
	case NEWVALUE:	newFSM = new (std::nothrow) FSMValue;	printf("Entering Value FSM\n"); break;
	//case NEWOBJ: newFSM = new (std::nothrow) FSMObject;		break;
	case NEWSTRING: newFSM = new (std::nothrow) FSMString;	printf("Entering String FSM\n"); break;
	case NEWNUM: newFSM = new (std::nothrow) FSMNumber;		printf("Entering Number FSM\n"); break;
	case NEWTRUE: newFSM = new (std::nothrow) FSMTrue;		printf("Entering True FSM\n"); break;
	case NEWFALSE: newFSM = new (std::nothrow) FSMFalse;	printf("Entering False FSM\n"); break;
	case NEWNULL: newFSM = new (std::nothrow) FSMNull;		printf("Entering Null FSM\n"); break;
	default: genericFSM* newFSM = NULL; break;
	}
	if (newFSM == NULL) {
		printf("Couldn't Create new FSM instance!\n");
	}
	else {
		stackLevel++;
		stack[stackLevel] = newFSM;
	}
}

void stackFSMsPop(genericFSM** stack, uint& stackLevel) {
	if ((stack[stackLevel]) != NULL) {
		delete stack[stackLevel];
		stackLevel--;
	}
}

void freeStack(genericFSM** stack, uint& stackLevel) {
	for (uint i = stackLevel; i > 0;) {
		stackFSMsPop(stack, i);
	}
}