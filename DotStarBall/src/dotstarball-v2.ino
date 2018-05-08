#include "JsonParserGeneratorRK.h"

// This #include statement was automatically added by the Particle IDE.
#include "CmdProcessorv2.h"

// This #include statement was automatically added by the Particle IDE.
#include <papertrail.h>

// This #include statement was automatically added by the Particle IDE.
#include "Repeater.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DotStar.h"

// This #include statement was automatically added by the Particle IDE.
#include "Animations.h"

// This #include statement was automatically added by the Particle IDE.
#include "Settings.h"

// This #include statement was automatically added by the Particle IDE.
#include "Sequencer.h"

// This #include statement was automatically added by the Particle IDE.
#include "Mode.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

UDP Udp;

Settings s;
Mode mo(0);
Sequencer sq;

Adafruit_DotStar st(s.NumPixels);
Animations a(&s,&st);

SerialLogHandler logHandler(115200, LOG_LEVEL_TRACE);
//PapertrailLogHandler papertrailHandler("logs3.papertrailapp.com", 16247, "DotStar Ball", (const char*)(System.deviceID()), LOG_LEVEL_TRACE);

int LED = D7;
bool LEDOn = false;
char msg[255];
bool Resets[3]; //LED, Time, UDP
bool loopDebug[5] = {false, false, false, false, false};
int loopCount = 0;
char jsonString[1500];

void setup() {
    //Start Serial for debugging messages.
    Serial.begin(115200);
    
    //Initialize Reset Array.
    InitializeResets();
    
    //LED Strip Initialization.
    InitializeLEDStrip();
    
    //Indicate startup via D7 LED...
    pinMode(LED, OUTPUT);    // sets pin as output
    digitalWrite(LED, HIGH); // sets the LED on
    delay(1000);
    digitalWrite(LED, LOW); // sets the LED off
    
    //Wait for serial debugging for 10 seconds. Flash D7 for visual indication.
    if (s.Debug) {
        long LastMillis = millis();
        while(!Serial.isConnected() && ( (millis() - LastMillis) < 10000 ) )
        {
            if (!LEDOn) {
                digitalWrite(LED, HIGH); // sets the LED on
            }
            else {
                digitalWrite(LED, LOW); // sets the LED off
            }
            LEDOn = !LEDOn;
            delay(200);
            Particle.process();
        }
    }
    digitalWrite(LED, LOW); // sets the LED off
    
    //Setup local time for Eastern Standard Time (UTC-5) and enable Daylight Savings Time.
    InitializeTime();

    //Start receiving commands via particle cloud.
    Log.info("Subscribing to \"DSBcmd\" events.");
    //if (s.Debug) { Serial.println("Subscribing to \"DSBcmd\" events."); }
    Particle.subscribe("DSBcmd", CmdSubscribeHandler, MY_DEVICES);
    Particle.connect();
    
    //Start UDP for receiving commands via wi-fi. Must call after Particle.connect().
    InitializeUDP();

    //if (s.Debug) { Serial.println(); } //Spacer...
}


void loop() {
    
    //Check for newly received commands.
    UdpReceive();
    
    //Process sequence changes.
    if ( (sq.Active && !(sq.SequenceComplete)) || sq.AdvanceNow ) {
        if (sq.AdvanceNow) {
            Log.warn("Advancing Sequence (Forced).");
            sq.Advance();
        } else if (mo.Complete && mo.Repeat == 0) {
            Log.warn("Advancing Sequence on Mode Complete.");
            sq.Advance();
        }
    }
    
    //Process the animation.
    if (mo.Step > 0) { mo.Delay = 0; }
    if ( ((millis() - mo.LastRunMillis) > (mo.NextMillis + mo.Delay)) ) {

        bool adv = false;
        //Reset the mode if repeat is enabled.
        if (mo.Complete) { adv = mo.AutoReset(); }

        if (!mo.Complete) {
            Log.warn("Mode Tick @ %u. Step %u. RepeatCount %i", millis(), mo.Step, mo.RepeatCount);
            
            //Process the animation.
            if (mo.Step <= mo.Steps) { a.ProcessMode(&mo); }
            
            //Advance the mode to the next step.
            mo.StepAdvance();
            
            Log.trace("End of Loop. Free memory: %u", System.freeMemory());
            
            //loopDebug = {true, true, true};
            //for(auto &v: loopDebug) { v = true; }
        }
    }
}

void CmdSubscribeHandler(const char *event, const char *data) 
{
    strcpy(jsonString, data);
    Log.warn("DSBcmd message received at %s.", Time.timeStr().c_str());
    Log.trace("...Payload: %s", jsonString);
    ParseNew(jsonString);
    ProcessResets();
}

void UdpReceive() 
{
    //strncpy(jsonString, *data, s.UDPMaxPacketSize);
    //char *message[s.UDPMaxPacketSize];
    //const char *message;
    bool rxError = true;
    
    int size = Udp.receivePacket((byte*)jsonString, s.UDPMaxPacketSize-1);
    if (size > 0 && size < s.UDPMaxPacketSize) {
        jsonString[size] = 0;
        rxError = false;
    } else if (size < 0) {
        Log.error("UDP receive size error: size = %i", size);
        rxError = true;
        // need to re-initialize on error
        Udp.begin(s.UDPPort);
    } 
    
    //Message receive was success... parse it.
    if (!rxError) {
        Log.trace("UDP message received from %i : %i:", Udp.remoteIP(), Udp.remotePort());
        Log.trace(jsonString);
        ParseNew(jsonString);
    }
}

void ProcessResets() {
    if (Resets[0]) {
        //Reset LED strip.
        InitializeLEDStrip();
    }
    if (Resets[1]) {
        //Reset Time zone/DST
        InitializeTime();
    }
    if (Resets[2]) {
        //Reset UPD.
        InitializeUDP();
    }
    InitializeResets();
}

void InitializeResets()
{
    for (int i=0; i<arraySize(Resets); i++) {
        Resets[i] = false;
    }
}

void InitializeLEDStrip() {
    //LED Strip Initialization.
    if (s.Debug) { Serial.printlnf("Initializing LED strip with %i pixels.", s.NumPixels); }
    if (s.NumPixels != st.numPixels()) { 
        if (s.Debug) { Serial.printlnf("Updating strip length to %i pixels.", s.NumPixels); }
        st.updateLength(s.NumPixels); 
    }
    st.begin();
    st.show();
    st.setBrightness(s.GBright);
}

void InitializeTime() {
    //Setup local time for Eastern Standard Time (UTC-5) and enable Daylight Savings Time.
    if (s.Debug) { Serial.printlnf("Initializing Time Zome (%i) and DST (%i)", s.TimeZoneOffset, s.EnableDST); }
    Time.zone(s.TimeZoneOffset);
    if (s.EnableDST) { Time.beginDST(); }
    if (s.Debug) { Serial.printlnf("The current time is %s.", Time.timeStr().c_str()); }
}

void InitializeUDP() {
    waitUntil(Particle.connected); //Network must be connected before calling Udp.begin() per photon reference.
    
    IPAddress myIP = WiFi.localIP();
    Log.warn("Local IP: %s; SSID: %s; RSSI: %i", myIP.toString().c_str(), WiFi.SSID(), WiFi.RSSI());
    
    //If a Udp setting changed, stop Udp then restart.
    if (Resets[2]) {
        Log.warn("Stopping UDP.");
        Udp.stop();
    }
    
    //Start UDP for receiving commands via wi-fi.
    Log.warn("Starting UDP on Port %d.", s.UDPPort);
    Udp.begin(s.UDPPort);
    Log.warn("Joining Multicast at address: %s", s.MCAddress.toString().c_str());
    Udp.joinMulticast(s.MCAddress);
}
