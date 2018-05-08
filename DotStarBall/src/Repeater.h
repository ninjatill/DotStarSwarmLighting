#ifndef __DOTSTAR_BALL_REPEATER__
#define __DOTSTAR_BALL_REPEATER__

#include "application.h"

class Repeater 
{
    public:
        int StepsToRepeat = 0;
        int RepeatLoops = 0;
        
        Repeater();
        
        String ToString();

};

#endif