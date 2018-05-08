
#include "application.h"
#include "Settings.h"
#include "Mode.h"

//****************************************************************************************************
//Variables updated by external commands.
//****************************************************************************************************

//Status variables.
uint8_t ID = 0;                 //ID number for this Mode.
unsigned long Duration =  0;     //Total amount of time to complete this mode/animation.
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
uint8_t Direction = 0;          //Direction of animation. 0=CW, 1=CCW, 254=Randomize, etc.

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

char msg_m[255] = "";


Mode::Mode() 
{
    //UpdateLastRun(true);
}

Mode::Mode(uint8_t ModeID) 
{
    ID = ModeID;
    //UpdateLastRun(true);
}

String Mode::ToString() 
{
    sprintf(msg_m, "Mode Core: ID:%i, Dur:%u, Stps:%u, Dly:%u, Rpt:%u, Cmplt:%i, WtE:%i, ExN:%i, Stp:%u, LstRM:%u, NxtM:%u",
        ID, Duration, Steps, Delay, Repeat, Complete, WaitToExec, ExecNow, Step, LastRunMillis, NextMillis
    );
        
    return msg_m;
}

String Mode::AnimationVariables() {
    sprintf(msg_m, "Mode Animation Vars: Clrs:%i, Objs:%i, W:%i, AdvCO:%i, CWS:%i, FadeWidth:%i, Dir:%i",
        ColorCount, ObjectCount, Width, AdvanceColorOn, ColorWheelSpeed, FadeWidth, Direction
    );
        
    return msg_m;
}

void Mode::UpdateLastRun(bool FirstRun) 
{
    //Trying to calculate the nextmillis as close to the duration as possible.
    //I'm estimating 9ms for SPI+Cloud overhead based on testing.
    //If too many stes and not enough duration, then do simple calc (which will stretch duration).
    if ( Duration >= (Steps*(s.EstimatedOverheadMillis)) ) {
        NextMillis = (Duration-(Steps*(s.EstimatedOverheadMillis))) / Steps;
    }
    else {
        NextMillis = Duration / Steps;
    }
    
    if (FirstRun) {
        LastRunMillis = millis() - NextMillis;
    } else {
        LastRunMillis = millis();
    }
    
    sprintf(msg_m,"Last run update: LastRunMillis: %u; NextMillis: %u", LastRunMillis, NextMillis);
    Log.trace(msg_m);
}

void Mode::StepAdvance() 
{
    if (Step > Steps) {
        Complete = true;
        Log.warn("Mode Complete. Time %s.", Time.timeStr().c_str());
    }
    else {
        Step++;
        Log.trace("Advancing to step %u.", Step);
        UpdateLastRun();
    }
}

bool Mode::AutoReset() 
{
    if (Complete && Repeat != 0 && Steps > 0) {
        Log.info("Repeating %i more times... Resetting mode.", Repeat);
        Step = 0;
        Complete = false;
        
        if (Repeat > 0) { 
            Repeat--; RepeatCount++; 
        } else if (Repeat < 0) {
            RepeatCount++;
        }
        return true;
    }
    return false;
}

uint32_t Mode::CurrentColor() 
{
    return FutureColor(0);
}

uint32_t Mode::FutureColor(int8_t Offset) 
{
    if ( ColorCount > 0 && ColorCount <= arraySize(Colors) ) {
        if (AdvanceColorOn == 1) {
            return Colors[((Step-1)+Offset) % ColorCount];
        } else if (AdvanceColorOn == 2) {
            return Colors[(RepeatCount+Offset) % ColorCount];
        } else {
            return 0x000001;
        }
    } else {
        return 0x000000;
    }
}

char Mode::ObjectType(uint8_t index) 
{
    if ( ObjectCount > 0 && ObjectCount < arraySize(Objects) ) {
        int i = index % ObjectCount;
        String myObj = Objects[index];
        if (myObj.length() > 1) {
            return myObj.charAt(0);
        }
        else {
            return 'A';
        }
    } else {
        return 'A';
    }
}

int Mode::ObjectIndex(uint8_t index) 
{
    if ( ObjectCount > 0 && ObjectCount < arraySize(Objects) ) {
        int i = index % ObjectCount;
        String myObj = Objects[index];
        if (myObj.length() > 1) {
            myObj = myObj.substring(1);
            if (IsInt(myObj)) {
                int v = myObj.toInt();
                if ( v>=0 && v<(s.NumPixels) ) {
                    return v;
                }
                else {
                    return (s.NumPixels) - 1;
                }
            }
            else {
                return -2;
            }
        }
        else {
            return -1;
        }
    } else {
        return 0;
    }
}

bool Mode::IsInt(String myString)
{
    bool test = true;
    for(int i=0;i<myString.length();i++)
    {
        if( !isDigit(myString.charAt(i)) ) {
            test = false;
        }
    }
    return test;
}










