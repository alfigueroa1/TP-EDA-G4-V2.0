
#ifndef EVENTS_H
#define EVENTS_H
#include <stdlib.h>
typedef short eventType;
typedef unsigned int uint;

#define NOEVENT '$'

eventType getNextEvent(FILE * m, int &line);

#endif /* EVENTS_H */

