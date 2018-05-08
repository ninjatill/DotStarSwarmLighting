
#include "application.h"
#include "Settings.h"
#include "Mode.h"
#include "Animations.h"
#include "Adafruit_DotStar.h"
#include <vector>
#include "math.h"

//Animations.cpp
Settings *s_a;
Adafruit_DotStar *st_a;
Mode *m_a;

uint16_t PixelsPerColumn = 0;
std::vector<uint16_t> Columns;
std::vector<uint16_t> Rows;
std::vector<uint16_t> Pixels;

Animations::Animations(Settings *settings, Adafruit_DotStar *strip) 
{
    s_a = settings;
    st_a = strip;
    PixelsPerColumn = ( s_a->NumPixels / (s_a->NumColumns) );
    Columns.resize(s_a->NumColumns);
    Pixels.resize(s_a->NumPixels);
    Rows.resize(s_a->NumRows);
}

void Animations::ProcessMode(Mode *mode) 
{
    m_a = mode;
    
    //Run the mode setup if neccessary. Will advance Step so all modes start with step 1.
    if (m_a->Step == 0) {
        SetupMode();
    }
    
    switch (m_a->ID) {
        case 0:    //No Mode/Standby (all Pixels off)
            if (s_a->Debug) { Serial.println("Processing mode 0: Standby"); }
            
            //Only clear the strip once then wait.
            if (m_a->Step == 1) {
                AllOff();
            }
            break;
            
        case 1:     //All Off using memset method
            if (s_a->Debug) { Serial.println("Processing mode 1: All Off"); }
            AllOff();
            break;
            
        case 2:     //Object On
            if (s_a->Debug) { Serial.println("Processing mode 2: Object On"); }
            ObjectsOn();
            break;
            
        case 11:    //Fade
            if (s_a->Debug) { Serial.println("Processing mode 11: Fade"); }
            Fade();
            break;
        case 12:    //Fill
            if (s_a->Debug) { Serial.println("Processing mode 12: Fill"); }
            Fill();
            break;
        
    }
    
    st_a->show();
}

void Animations::SetupMode() 
{
    switch (m_a->ID) {
        case 11: //Fade
            m_a->AdvanceColorOn = 2; //Force advance on repeat.
            break;
        case 12: //Fill
            InitializeVectors();
            //st_a->clear();
            break;
        default:
        
            break;
            
    }
    
    if (s_a->Debug) { Serial.println("Animation setup complete. Starting Step 1..."); }
    //All modes process from Step 1.
    (m_a->Step) = 1;
}

void Animations::InitializeVectors() {
    bool t[] = {false,false,false};
    for (int i=0; i<arraySize(m_a->Objects); i++) {
        char c = m_a->ObjectType(i);
        if (c == 'C') { t[0] = true; }
        else if (c == 'P') { t[1] = true; }
        else if (c == 'R') { t[2] = true; }
    }
    
    //Calculate if we should reverse the vectors.
    bool Reverse = false;
    switch (m_a->Direction) {
        case 1:
            Reverse = true;
            break;
        case 2:
            if (m_a->Step%2 == 1) { Reverse = true; }
            break;
        case 3:
            if (m_a->Step%2 == 0) { Reverse = true; }
            break;
        case 4:
            if (m_a->RepeatCount%2 == 1) { Reverse = true; }
            break;
        case 5:
            if (m_a->RepeatCount%2 == 1) { Reverse = true; }
            break;
    }
    if (t[0]) { InitializeColumns(Reverse); }   
    if (t[1]) { InitializePixels(Reverse); } 
    if (t[1]) { InitializeRows(Reverse); } 
    
    if (m_a->Direction == 254) {
        if (s_a->Debug) { Serial.println("Randomizing object vectors."); }
        if (t[0]) { RandomizeVector(&Columns); }   
        if (t[1]) { RandomizeVector(&Pixels); } 
        if (t[2]) { RandomizeVector(&Rows); } 
    }
}

void Animations::InitializeColumns(bool Reverse) {
    int s = Columns.size();
    for (int i=0; i<s; i++) {
        if (Reverse) {
            Columns[i] = i;
        } else {
            Columns[i] = (s-i)-1;
        }
    }
}

void Animations::InitializePixels(bool Reverse) {
    int s = Pixels.size();
    for (int i=0; i<s; i++) {
        if (Reverse) {
            Pixels[i] = i;
        } else {
            Pixels[i] = (s-i)-1;
        }
    }
}

void Animations::InitializeRows(bool Reverse) {
    int s = Rows.size();
    for (int i=0; i<s; i++) {
        if (Reverse) {
            Rows[i] = i;
        } else {
            Rows[i] = (s-i)-1;
        }
    }
}

void Animations::RandomizeVector(std::vector<uint16_t> *v) 
{
    // next 3 lines are for randomizing the randomgenerator.
    //randomSeed(micros());
    
    //Randomly swap array positions.
    int count = 0;
    int s = (*v).size();
    for (int i= 0; i<s; i++) 
    {
        int pos = random(s);
        int t = (*v)[i];   
        (*v)[i] = (*v)[pos];
        (*v)[pos] = t;
        count++;
    }
    if (s_a->Debug) { Serial.printlnf(".Randomized %i positions.", count); }
}

//The memset method of clearing a strip should be faster than
//using the AllOn method with the color "black".
void Animations::AllOff() 
{
    if (s_a->Debug) { Serial.println("...All Off"); }
    st_a->clear();
}


//Turns on all objects in mode with color advanced by step or repeat.
void Animations::ObjectsOn() 
{
    if (s_a->Debug) { Serial.println("...Objects On. Using Color Array."); }
    uint32_t currentColor = CurrentColor();
    ProcessObjects(currentColor);
}   

//Turns on all object in mode with arbitrary color (used by fade, color wheel, etc.)
void Animations::ObjectsOn(uint32_t Color) 
{
    if (s_a->Debug) { Serial.println("...Objects On. Specified Color."); }
    ProcessObjects(Color);
}

//Cycles through mode object array and sets all objects to specified color.
void Animations::ProcessObjects(uint32_t Color) 
{
    if (m_a->ObjectCount == 0) { //No objects specified = All On.
        if (s_a->Debug) { Serial.println("...No object array. Default to All."); }
        AllOn(Color);
    } else {
        for (int i=0; i<(m_a->ObjectCount); i++) {
            char objType = m_a->ObjectType(i);
            int objIndex = m_a->ObjectIndex(i);
            ObjectOn(objType, objIndex, Color);
        }
    }
}

//Turns on a single object with specified color.
void Animations::ObjectOn(char ObjectType, int ObjectIndex, uint32_t Color, int ObjectOffset) 
{
    Log.trace("...Object On O:%c I:%i CHex: %#06X CDec: %i", ObjectType, ObjectIndex, Color, Color);
    
    if (ObjectType == 'A') {
        AllOn(Color);
    } else if (ObjectType == 'C') {
        ColumnOn(ObjectIndex, Color);
    } else if (ObjectType == 'R') {
        RowOn(ObjectIndex, Color);
    } else if (ObjectType = 'P') {
        SingleOn(ObjectIndex, Color);
    }
    
}

void Animations::AllOn(uint32_t Color) 
{
    //uint32_t color = (r << 16) | (g << 8) | b;
    Log.trace("....All On: Color %#06X", Color);
        
    for (int i=0;i<st_a->numPixels();i++) {
        if (s_a->Trace) { Serial.print(String(i)); Serial.print(";"); }
        st_a->setPixelColor(i, Color);
        //Strip.setBrightness(Brightness);
    }
    
    if (s_a->Trace) { Serial.println(); }
}

void Animations::SingleOn(uint16_t PixelIndex, uint32_t Color, int Offset) 
{
    Log.trace("....Single On");
    int pi = (PixelIndex + Offset) % (s_a->NumPixels); //Accounts for an erroneously large index or offset.
    st_a->setPixelColor(pi, Color);
    
}

void Animations::ColumnOn(uint8_t ColumnIndex, uint32_t Color, int Offset) 
{
    Log.trace("....Column On");
    int ci = (ColumnIndex + Offset) % s_a->NumColumns; //Accounts for an erroneously large index.
    for (int i = PixelsPerColumn * ci; i < PixelsPerColumn * (ci + 1); i++) {
        st_a->setPixelColor(i, Color);
    }
}

//The phyical LEDs are soldered in columns and each column is soldered so that
//the LED indexes of odd number columns are opposite the even numbered columns.
//Therefore, a row cannot be addressed the same as a column. Rather, the calculation
//for row pixels must be calculated separately for odd and even number columns.
void Animations::RowOn(uint8_t RowIndex, uint32_t Color, int Offset) 
{
    Log.trace("....Row On");
    int ri = (RowIndex + Offset) % (s_a->NumRows); //Accounts for an erroneously large pixel index.
    
    //Set all the pixels in even number columns.
    uint8_t iteration = 0;
    for (int i = ri; i < st_a->numPixels(); i = ri + (PixelsPerColumn * (iteration++ * 2)) ) {
        st_a->setPixelColor(i, Color);
    }
    
    //Set all the pixels in odd number columns.
    iteration = 0;
    for (int i = PixelsPerColumn + (PixelsPerColumn - ri); i < st_a->numPixels(); i = (PixelsPerColumn + (PixelsPerColumn - ri)) + (PixelsPerColumn * (iteration++ * 2)) ) {
        st_a->setPixelColor(i, Color);
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition R -> G -> B -> back to R.
uint32_t Animations::WheelColor(uint8_t WheelPos, uint8_t Speed) 
{
    WheelPos = 255 - WheelPos;
    if (Speed < 1) { Speed = 1; }
    if (WheelPos < 85) {
        return st_a->Color(255 - (WheelPos * Speed), 0, (WheelPos * Speed));
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return st_a->Color(0, WheelPos * Speed, 255 - WheelPos * Speed);
    } else {
        WheelPos -= 170;
        return st_a->Color(WheelPos * Speed, 255 - WheelPos * Speed, 0);
    }
}

uint32_t Animations::CurrentColor(int Offset)
{
    if (m_a->ColorWheelSpeed > 0) {
        return WheelColor((m_a->Step)%255);
    } else {
        return m_a->FutureColor(Offset);
    }
}

//Fade will transition between colors in the color array. At least 2 colors are required.
//On each repeat, the next 2 colors in the array will be used.
//For example, if the color array contians [Red, Green, Blue],
//on first pass it will fade from Red to Green. On the second pass
//it will fade from Green to Blue.
//Requirements: At least 2 colors specified, more than 2 steps.
void Animations::Fade() 
{
    if ( 
        (m_a->ColorCount > 1) 
        && m_a->Steps > 2
    ) {
        uint32_t StartColor = m_a->CurrentColor();
        uint32_t EndColor = m_a->FutureColor(1);
        
        Log.trace("..StartC: Hex:%#06X Dec:%i, EndC: Hex:%#06X Dec:%i", StartColor, StartColor, EndColor, EndColor);
        //if (s_a->Debug) { Serial.print(".StartC: "); Serial.print(StartColor, HEX); Serial.print(", EndC: ", ); Serial.print(EndColor, HEX); Serial.println(); }
        
        if (m_a->Step == 1) {
            ObjectsOn(StartColor);
        } else if (m_a->Step == m_a->Steps) {
            ObjectsOn(EndColor);
        } else if (StartColor != EndColor) {
            uint8_t RGBStart[3] = {(uint8_t)(StartColor >> 16), (uint8_t)(StartColor >> 8), (uint8_t)(StartColor)};
            uint8_t RGBEnd[3] = {(uint8_t)(EndColor >> 16), (uint8_t)(EndColor >> 8), (uint8_t)(EndColor)};
            float RGBStep[3];
            uint8_t RGBMid[3];
            
            //This doesn't work... wouldn't do negative values.
            //int16_t StepTrans[3];
            //for (int i=0; i<arraySize(StepTrans); i++) {
            //    StepTrans[i] = ( (int16_t)(RGBEnd[i]) - (int16_t)(RGBStart[i]) ) / ((m_a->Steps)-1);
            //}

            for (int i=0; i<arraySize(RGBMid); i++) {
                if (RGBStart[i] >= RGBEnd[i]) {
                    RGBStep[i] = (RGBStart[i] - RGBEnd[i])/((m_a->Steps)-1);
                    RGBMid[i] = RGBStart[i] - ( RGBStep[i] * ((m_a->Step)-1) );
                    //if (s_a->Debug) { Serial.printlnf("..Start >= End for %i. Total decrement: %.2f", i, RGBStep[i] * ((m_a->Step)-1) ); }
                } else {
                    RGBStep[i] = (RGBEnd[i] - RGBStart[i])/((m_a->Steps)-1);
                    RGBMid[i] = RGBStart[i] + ( RGBStep[i] * ((m_a->Step)-1) );
                    //if (s_a->Debug) { Serial.printlnf("..Start < End for %i. Total increment: %.2f", i, RGBStep[i] * ((m_a->Step)-1) ); }
                }
            }
            
            //if (s_a->Debug) { Serial.printlnf("..RGBSteps: R:%.2f G:%.2f B:%.2f", RGBStep[0], RGBStep[1], RGBStep[2]); }
            
            ObjectsOn(st_a->Color(RGBMid[0], RGBMid[1], RGBMid[2]));
        }
    }
}

void Animations::Fill()
{
    //if (s_a->Debug) { Serial.printlnf("..StartC: Hex:%#06X Dec:%i, EndC: Hex:%#06X Dec:%i", StartColor, StartColor, EndColor, EndColor); }
    uint32_t Color = CurrentColor(); //Get the color.
    uint32_t PColor = CurrentColor(-1); //Get the previous color.
    
    for (int i=0; i<arraySize(m_a->Objects); i++) {
        char c = m_a->ObjectType(i);
        int x = m_a->ObjectIndex(i);
        if (c == 'C') { 
            float stepInc = (float)(s_a->NumColumns) / m_a->Steps;
            Log.trace("..C Step Increment: %f, Obj Offset: %i", stepInc, x);
            for (int i = 0; i < s_a->NumColumns; i++) {
                int bot = floor((m_a->Step-1) * stepInc);
                int top = (m_a->Step) * stepInc;
                if (m_a->Step == m_a->Steps) { top = ceil((m_a->Step) * stepInc); }
                if ( i >= bot && i <= top ) {
                    ObjectOn('C', Columns[i], Color, x);
                }
                
                //Use width to turn create a spin by turning off tail.
                if (m_a->Width <> 0 && abs(m_a->Width) >= m_a->Step ) {
                    if ( i<((top - m_a->Width) % s_a->NumColumns) && i > top ) {
                        if (m_a->ColorCount > 1) {
                            ObjectOn('C', Columns[i], PColor, x);
                        } else {
                            ObjectOn('C', Columns[i], 0x000000, x);
                        }
                    }
                }
            }
        }
        else if (c == 'P') { 
            float stepInc = (float)(s_a->NumPixels) / m_a->Steps;
            Log.trace("..P Step Increment: %f, Obj Offset: %i", stepInc, x);
            for (int i = 0; i < s_a->NumPixels; i++) {
                int bot = floor((m_a->Step-1) * stepInc);
                int top = (m_a->Step) * stepInc;
                if (m_a->Step == m_a->Steps) { top = ceil((m_a->Step) * stepInc); }
                if ( i >= bot && i <= top ) {
                    ObjectOn('P', Pixels[i], Color, x);
                }
                
                //Use width to create a spin by turning off tail.
                if (m_a->Width <> 0) {
                    if ( i<((top - m_a->Width) % s_a->NumPixels) && i > top ) {
                        if (m_a->ColorCount > 1) {
                            ObjectOn('P', Pixels[i], PColor, x);
                        } else {
                            ObjectOn('P', Pixels[i], 0x000000, x);
                        }
                    }
                }
            } 
        }
        else if (c == 'R') { 
            float stepInc = (float)(s_a->NumRows) / m_a->Steps;
            Log.trace("..R Step Increment: %f, Obj Offset: %i", stepInc, x);
            for (int i = 0; i < s_a->NumRows; i++) {
                int bot = floor((m_a->Step-1) * stepInc);
                int top = (m_a->Step) * stepInc;
                if (m_a->Step == m_a->Steps) { top = ceil((m_a->Step) * stepInc); }
                if ( i >= bot && i <= top ) {
                    ObjectOn('R', Rows[i], Color, x);
                }
                
                //Use width to turn create a spin by turning off tail.
                if (m_a->Width <> 0) {
                    if ( i<((top - m_a->Width) % s_a->NumRows) && i > top ) {
                        if (m_a->ColorCount > 1) {
                            ObjectOn('R', Rows[i], PColor, x);
                        } else {
                            ObjectOn('R', Rows[i], 0x000000, x);
                        }
                    }
                }
            } 
        } //if obj type
    } //for
}

void Animations::Spin() 
{
    
}

//Lights a portion of the pixels and
void Animations::Twinkle()
{
    
}


