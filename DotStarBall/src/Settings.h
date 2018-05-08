
#ifndef __DOTSTAR_BALL_SETTINGS__
#define __DOTSTAR_BALL_SETTINGS__

#include "application.h"

class Settings {
    public:
    
        //********************
        //Variables
        //********************
        
        bool Debug = true; //Enables debugging messages to serial console.
        bool Trace = false; //Enables trace messages to serial console.

        uint8_t GBright = 32; //Global Brightness Level
        uint16_t NumPixels = 552; //Number of Pixels in Ball.
        uint8_t NumColumns = 24; //Number of Columns in Ball.
        uint8_t NumRows = 23; //Number of Rows in Ball.
        
        char SwarmID = 'A'; //Groups devices into a addressable swarm.
        char HGroup = 'B'; //Horizontal Grouping within Swarm
        char VGroup = 'C'; //Vertical Grouping within Swarm
        
        uint16_t UDPPort = 8023;    //UDP listening port.
        uint16_t UDPMaxPacketSize = 1500;   //Network MTU size.
        IPAddress MCAddress;   //Multicast Address for Receiving Commands
        
        int8_t TimeZoneOffset = -5; //Offset from UTC for current time zone.
        bool EnableDST = true;      //Account for Daylight Savings Time; True = yes.
        
        int EstimatedOverheadMillis = 12; //Estimate 12 ms for SPI and cloud overhead.
        
        //********************
        //Functions
        //********************
        Settings();
        
        String ToString();

};

#endif