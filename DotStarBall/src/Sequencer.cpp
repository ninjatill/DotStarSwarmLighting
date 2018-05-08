#include "application.h"
#include "Sequencer.h"
#include "Mode.h"
#include "Repeater.h"
#include "Settings.h"
#include <vector>
#include <map>


uint8_t pi = 0;         //Processing Index. Index of current element being processed.
bool Active = false;    //Used to indicate that the sequence is active and processing should occur.
bool AdvanceNow = false;
bool SequenceComplete = false;

std::vector<String> Elements;      //List of Modes in this sequence. Modes stored as JSON string.
std::map<uint8_t, int> RepeatTracker;    //Tracks how many times the current repeat step has repeated so far.

Sequencer::Sequencer() {
}


//Advances to the next element in the sequence.
void Sequencer::Advance() {
    if (pi >= 0 && pi < Elements.size()) {          //Check the index is within bounds of Elements container.
        String full = Elements[pi];
        String type = CmdElementType(&full);
        
        Log.trace("Parsing Element (%i): Type: %s, Full: %s", pi, type.c_str(), full.c_str());
        if (strcmp(type,"M") == 0) {  //Mode Element
            Log.trace("...Processing a Mode change.");
            Mode mode(0); //Create a new mode.
            ParseMode(full, &mode);  //Populate the new mode.
            mo = mode;    //Assign the new mode into the global mode for processing.
            AdvanceNow = false;
            pi++;
        } else if (strcmp(type,"R") == 0) { //Repeat Element
            Log.trace("...Processing a Repeater.");
            Repeater rep;                       //Create a new repeater element.
            ParseRepeater(full, &rep);          //Populate the new repeater.
            
            std::map<uint8_t, int>::iterator mit;   //Create an iterator to test for this repeat index in the tracker.
            mit = RepeatTracker.find(pi);       //Find the repeat element if it exists.
            
            if (mit != RepeatTracker.end()) {   //Repeat index exists.
                
                if (RepeatTracker[pi] == rep.RepeatLoops) { //Repeat is complete.
                    Log.trace("Repeater @ index %i complete.", pi);
                    RepeatTracker.erase(pi);    //Remove the Repeat index from the tracker.
                    pi++;
                    return;
                } else {                        //Repeat is not complete. 
                    RepeatTracker[pi]++;        //Increment the counter for this repeat.
                }
            } else {                            //Repeat index does not exist in the tracker.
                RepeatTracker[pi] = 1;          //Add the repeat index in the tracker.
            }
            
            AdvanceNow = false;
             
            if (pi - rep.StepsToRepeat >= 0) {            //Only adjust the processing index if it will be within bounds of the Elements container.
                pi = pi - (rep.StepsToRepeat);            //Decrement the processing index by the number of elements to repeat.
            } else { 
                pi = 0;
            }
            
            Log.trace(ToString());
        } else if (strcmp(type,"S") == 0) { //Settings Element.
            Log.trace("...Processing a Settings update.");
            ParseSettings(full, &s);
            AdvanceNow = true;
            pi++;
        } else {
            Log.error("Element type not recognized.");
            pi++;
        }
    } else {
       SequenceComplete = true; //Mark the sequence complete.
       AdvanceNow = false;
    }
    
}

String Sequencer::ToString() {
    char msgs[255];
    sprintf(msgs, "Sequence: PI:%i, Act:%i, AdvN:%i, SC:%i, ECnt:%i", pi, Active, AdvanceNow, SequenceComplete, Elements.size());

    return msgs;
}

//Adds an element to the end of the sequence.
void Sequencer::Add(String JsonString) {
    Elements.push_back(JsonString);
}

int Sequencer::Length() {
    return Elements.size();
}



