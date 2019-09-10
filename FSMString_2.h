#ifndef _FSMSTRING_2_H
#define _FSMSTRING_2_H

#include "genericFSM.h"
#include "events.h"
#include "FSMstates.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

class FSMString:public genericFSM{

public:
    FSMString() {
        rowCount = 6;
        done = false;
        state = strState0;
    }
    virtual int filterEvents(eventType ev) {
        char * evento;
        if(ev != EOF)
            evento = (char*) ev;
        else
            return 0;
        regex_t preg;
        const char *regex_char = "^[ac-eg-mo-qsv-zG-TV-Z]$";
        const char *regex_quote = "^\"$";
        const char *regex_rsolidus = "^\\\\$";
        const char *regex_symb = "^[fnrt/]$";
        const char *regex_u = "^[uU]$";
        const char *regex_hex = "^[0-9a-fA-F]$";

        /* Digit */
        if (!regcomp (&preg, regex_char, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 2;
            }
        }

        /* Quote */
        if (!regcomp (&preg, regex_quote, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 1;
            }
        }

        /* Reverse solidus */
        if (!regcomp (&preg, regex_rsolidus, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 3;
            }
        }

        /* U */
        if (!regcomp (&preg, regex_u, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 4;
            }
        }

        /* Hexa */
        if (!regcomp (&preg, regex_hex, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 5;
            }
        }

        /* Symbol */
        if (!regcomp (&preg, regex_symb, REG_NOSUB | REG_EXTENDED))
        {
            if( !regexec (&preg, evento, 0, NULL, 0)){
                regfree (&preg);
                return 6;
            }
        }
        return 0;
    }
    virtual void cycle(eventType* ev) {
        eventType evento;
        int i = 0, j = 0;
        evento = filterEvents(*ev);
        i = evento;
        switch (state) {
            case strState0:	j = 0; break;
            case strState1:	j = 1; break;
            case strState2:	j = 2; break;
            case strState3:	j = 3; break;
            case strState4:	j = 4; break;
        }
        state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
        FSMTable[(j * rowCount) + (evento - 1)].action;
    }

private:
#define SX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMString::x))

    const fsmCell FSMTable[24] = {

            // Recibir "            // Recibir char         // Recibir \            // Recibir u            // Recibir 4hex             // Recibir symb
            {strState1, TX(strNop)},  {ERROR, TX(strNop)},   {ERROR, TX(strNop)},   {ERROR, TX(strNop)},   {ERROR, TX(strNop)},      {ERROR, TX(strNop)},
            {FIN, TX(strNop)},	    {strState1, TX(strNop)},  {strState2, TX(strNop)},  {strState1, TX(strNop)},  {strState1, TX(strNop)},     {strState1, TX(strNop)},
            {strState3, TX(strNop)},	{ERROR, TX(strNop)},   {strState3, TX(strNop)},   {state4, TX(strNop)},  {ERROR, TX(strNop)},     {strState3, TX(strNop)},
            {FIN, TX(strNop)},	    {strState1, TX(strNop)}, 	{strState2, TX(strNop)},  {strState1, TX(strNop)},	{strState1, TX(strNop)},     {strState1, TX(strNop)},
            {ERROR, TX(strNop)},   {ERROR, TX(strNop)},   {ERROR, TX(strNop)},   {ERROR, TX(strNop)},   {strState3, TX(strNop)},     {ERROR, TX(strNop)},
    };
    void strNop(eventType* ev) {
        return;
    }

};

#endif //_FSMSTRING_2_H