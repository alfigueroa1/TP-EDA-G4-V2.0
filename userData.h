#ifndef USERDATA_H
#define USERDATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* --- Structs declaracion --- */

// Callback declaracion
typedef int (*pCallback) (char *, char *, void *);

// Nombre de las funciones
typedef enum {file} optionType;

// Tipos de operaciones
typedef struct {
    optionType op;
    char *name;
    pCallback action;
} operation;

// Datos

typedef struct {
    FILE* file;
}argTypes;

int loadFile(char *key, char *value, void *userData);
int parseCallback (char *key, char *value, void *userData);

#endif
