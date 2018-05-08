
#ifndef __DOTSTAR_BALL_SEQUENCER__
#define __DOTSTAR_BALL_SEQUENCER__

#include "application.h"
#include "Mode.h"
#include "Repeater.h"
#include "Settings.h"
#include "CmdProcessorv2.h"
//#include <SparkJson.h>
#include <vector>
#include <map>

extern Settings s;
extern Mode mo;              //Pointer to the global mode instance.

class Sequencer 
{
    public:
        
        bool Active = false;    //Used to indicate that the sequence is active and processing should occur.
        bool AdvanceNow = false;
        bool SequenceComplete = false;
        
        std::vector<String> Elements;      //List of elements (modes, settings, ets,) in this sequence.
        std::map<uint8_t, int> RepeatTracker;    //Tracks number of repeats when a repeat element is encountered.
    
        Sequencer();
        
        void Advance();         //Advances to the next element in the sequence.
        void Add(String JsonString);
        int Length();
        String ToString();
    
    private:
        uint8_t pi = 0;         //The current sequnce step.
        
        
};



#endif