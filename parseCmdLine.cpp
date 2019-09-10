//
// Created by Arthur on 10/09/2019.
//

#include "parseCmdLine.h"
#include "userData.h"

int parseCmdLine (int argc, char *argv[], pCallback p, void *userData)
{
    char *key;
    char *value;

    int nOutput = 0;

    int i;
    //Parse cada arg despues del primero
    for (i=1; i<argc; i++)
    {
        //Opcion
        if(argv[i][0]=='-' && argv[i+1]!=NULL)
        {
            key = argv[i];
            i++;
            value = argv[i];
        }
            //Parametro
        else
        {
            key = NULL;
            value = argv[i];
        }


        //Prueba si el argumento es valido
        if(p(key, value, userData))
        {
            nOutput++;
        }
        else
        {
            // Error
            return -1;
        }

    }

    return nOutput;
}
