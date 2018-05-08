
#include "application.h" 
#include "Settings.h"


//********************
//Variables
//********************

bool Debug = true;          //Enables debugging messages to serial console.
bool Trace = false;         //Enbles trace messages to serial console.

uint8_t GBright = 128;      //Global Brightness Level
uint16_t NumPixels = 552;   //Number of Pixels in Ball.
uint8_t NumColumns = 24;    //Number of Columns in Ball.
uint8_t NumRows = 23;       //Number of Rows in Ball.

char SwarmID = 'A';         //Groups devices into a addressable swarm.
char HGroup = 'B';          //Horizontal Grouping within Swarm
char VGroup = 'C';          //Vertical Grouping within Swarm
char IDWildcard = '-';      //Configurable wildcard character for any of the SWARM ID or Groups above.

uint16_t UDPPort = 8023;    //UDP listening port.
uint16_t UDPMaxPacketSize = 1500;   //Network MTU size.
IPAddress MCAddress(239,1,1,243);   //Multicast Address for Receiving Commands

int8_t TimeZoneOffset = -5; //Offset from UTC for current time zone. -5=EST
bool EnableDST = true;

int EstimatedOverheadMillis = 12; //Estimate 12 ms for SPI and cloud overhead.

//********************
//Functions
//********************
Settings::Settings() {
    uint8_t server[] = {239,1,1,243};
    MCAddress = server;
}

String Settings::ToString() {
    char result[255];
    sprintf(result, "Settings: FullSwarm:%c%c%c, WC:%c, Debug:%i, Trace:%i, GBright:%i, UPort:%i, USize:%i, MCIP:%i, UTCoff:%i, DSTenable:%i",
        SwarmID, HGroup, VGroup, IDWildcard, Debug, Trace, GBright, UDPPort, UDPMaxPacketSize, MCAddress, TimeZoneOffset, EnableDST
    );
        
    return result;
}
