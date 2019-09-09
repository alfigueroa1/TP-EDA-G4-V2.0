#include <iostream>
#include "events.h"

using namespace std;

const char entradas[] = {EOF, '(', ')', '{', '}', ']', '[', '"', ':', '/', 'f', 'n', 'r', 't', 'b', ','
						, '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '-', '+'
						, 'r' , 'u' , 'e' , 'E' , 'a' , 'l' , 's' , 'u', 'l' };

eventType getNextEvent(FILE* archivo, int &line){
    short caracter;
    caracter = fgetc(archivo);
	if (caracter == (short)0x000D || caracter == (short)0x000A)
		line++;
    for(int i = 0; i < (sizeof(entradas)/sizeof(char)); i++){
        if(caracter == entradas[i])
            return caracter;
    }
    return NOEVENT;
}

