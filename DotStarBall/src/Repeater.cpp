
#include "application.h"
#include "Repeater.h"

//****************************************************************************************************
//Repeater Element 
//****************************************************************************************************
int StepsToRepeat = 0;
int RepeatLoops = 0;

Repeater::Repeater() {
    
}

String Repeater::ToString() {
    char msgs[255];
    sprintf(msgs, "Repeater: StR:%i, RL:%i", StepsToRepeat, RepeatLoops);

    return msgs;
}



