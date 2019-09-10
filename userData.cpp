#include "userData.h"

/* --- Declaracion de las opciones --- */
operation opFile = {file, (char*) "-file", (pCallback) &loadFile};

/* --- Declaracion de las funciones --- */

int loadFile(char *key, char *value, void *userData){
    FILE* archivo;
    archivo = fopen(value, "r");
    if (archivo == NULL)
    {
        return 0;
    }


    argTypes* arg = (argTypes*) userData;
    arg->file = archivo;

    return 1;
}

// Verifica si los argumentos (opcion o parametro) existen
int parseCallback (char *key, char *value, void *userData)
{
    //Opcion
    if(key!=NULL)
    {
        //Buscamos si la opcion existe
        if (strcmp(key, opFile.name)==0 && value!=NULL)
        {
            if(opFile.action(key, value, userData))
                return 1;
        }
    }

    return 0;
}