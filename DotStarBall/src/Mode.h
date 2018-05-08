
#ifndef __DOTSTAR_BALL_MODE__
#define __DOTSTAR_BALL_MODE__

#include "application.h"
#include "Settings.h"

extern Settings s;

class Mode {
    public:
    
        //****************************************************************************************************
        //Variables updated by external commands.
        //****************************************************************************************************
        
        //Status variables.
        uint8_t ID = 0;                 //ID number for this Mode.
        unsigned long Duration = 0;     //Total amount of time to complete this mode/animation.
        unsigned long Steps = 1;        //Total number of processing steps to complete this mode.
        unsigned long Delay = 0;        //Delay in millis() before starting the animation.
        int Repeat = 0;                 //0=No Repeat; Positive Values=Number of times to repeat; Negative Values = Repeat Indefinitely.

        bool WaitToExec = false;        //If set to true, then an "execute" command must be received before processing this mode.
        bool ExecNow = false;           //Used to indicate that an execute command was received.
        
        //Animation Variables
        uint32_t Colors[32];            //An array of Colors. Only 24 LSB's are used.
        String Objects[32];             //An array of Objects. Examples:  "C1"=Column 1, "P344"=Pixel 344, "R10"=Row 10
        
        int Width = 0;                  //Sets the width of the animations (such as number of objects lit during a spin.)
        int FadeWidth = 0;              //Width of the tail fade.
        int AdvanceColorOn = 0;         //When multiple colors defined, when do we advance to next color? 1=Step, 2=Repeat
        uint8_t ColorWheelSpeed = 0;    //Changes the speed of the color wheel cycle. smaller number slower than large numbers.
        uint8_t Direction = 0;          //Direction of animation. Value list below: 
                                            //0=CW, 1=CCW, 2=CW rev on Step, 3=CCW rev on Step, 4=CW rev on Repeat, 5=CCW rev on Repeat,
                                            //6=
                                            //254=Randomize, etc.
        
        //****************************************************************************************************
        //Variables used for mode status but not set by external commands.
        //****************************************************************************************************
        unsigned long Step = 0;         //Current processing step.
        unsigned long LastRunMillis = 0;//Time in millis() that the last step ran.
        unsigned long NextMillis = 0;   //Number of milliseconds till next step.
        int RepeatCount = 0;            //Advances each time the mode repeats.
        bool Complete = true;           //Set this flag to true when the mode has completed. (Used to tell base code to move to the next step in the sequence or to repeat.)
        uint8_t ColorCount = 0;         //Total number of colors to process (number of active elements in Colors[]).
        uint8_t ObjectCount = 0;        //Total number of objects to process (number of active elements in Objects[]).
        
        //********************
        //Functions
        //********************
        Mode();
        Mode(uint8_t ModeID);
        
        String ToString();              //Provides a string with all status variables.
        String AnimationVariables();    //Provides a string with all animation variables.

        void StepAdvance();             //Advances mode to the next step.
        void UpdateLastRun(bool FirstRun = false);  //Updates last run millis.
        bool AutoReset();               //Resets the mode if repeat is enabled (complete flag, step count, repeat count, etc.)
        
        uint32_t CurrentColor();        //Retrieves a FutureColor with offset = 0 (current color);
        uint32_t FutureColor(int8_t Offset);  //Retrives a color from Colors array based on an offset from the current Step or RepeatCount.
        char ObjectType(uint8_t Index); //Get the the object type from the Objects array using the supplied array index.
        int ObjectIndex(uint8_t Index); //Get the the object index from the Objects array using the supplied array index.
        
    private:
        
        char msg[255] = "";
        bool IsInt(String myString);
};

#endif