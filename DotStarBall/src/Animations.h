
//Animations.h

#ifndef __DOTSTAR_BALL_ANIMATIONS__
#define __DOTSTAR_BALL_ANIMATIONS__

#include "application.h"
#include "Settings.h"
#include "Mode.h"
#include "Adafruit_DotStar.h"
#include <vector>

class Animations 
{
    public:
    
        //********************
        //Variables
        //********************
        
        
        
        
        //********************
        //Functions
        //********************
        Animations(Settings *settings, Adafruit_DotStar *strip);
        
        void ProcessMode(Mode *mode);
        
    private:
        Settings *s_a;
        Adafruit_DotStar *st_a;
        Mode *m_a;
        
        uint16_t PixelsPerColumn = 0;
        std::vector<uint16_t> Columns;
        std::vector<uint16_t> Rows;
        std::vector<uint16_t> Pixels;
        
        void SetupMode();
        void InitializeVectors();
        void InitializeColumns(bool Reverse = false);
        void InitializePixels(bool Reverse = false);
        void InitializeRows(bool Reverse = false);
        void RandomizeVector(std::vector<uint16_t> *v);
        
        void AllOff();
        void ObjectsOn();
        void ObjectsOn(uint32_t Color);
        void ProcessObjects(uint32_t Color);
        void ObjectOn(char ObjectType, int ObjectIndex, uint32_t Color, int ObjectOffset = 0);
        
        void AllOn(uint32_t Color);
        void ColumnOn(uint8_t ColumnIndex, uint32_t Color, int Offset = 0);
        void RowOn(uint8_t RowIndex, uint32_t Color, int Offset = 0);
        void SingleOn(uint16_t PixelIndex, uint32_t Color, int Offset = 0);
        
        uint32_t WheelColor(uint8_t WheelPos, uint8_t Speed = 1);
        uint32_t CurrentColor(int Offset = 0);
        
        void Fade();
        void Fill();
        void Spin();
        void Twinkle();

};

#endif