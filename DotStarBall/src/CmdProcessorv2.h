
#ifndef __DOTSTAR_BALL_CMDPROCESSORv2__
#define __DOTSTAR_BALL_CMDPROCESSORv2__

#include "application.h"
#include "Settings.h"
#include "Mode.h"
#include "Repeater.h"
#include "Sequencer.h"

// This #include statement was automatically added by the Particle IDE.
#include "JsonParserGeneratorRK.h"

class Sequencer; //Forward Declaration.

extern Settings s;
extern Mode mo;
extern Sequencer sq;
extern bool Resets[3];
extern char msg[255];

//JsonParserStatic<2000, 100> jparser;

void ParseNew(char *NewCmd);
String CmdElementType(String *JsonString);
String CmdElementType(char *JsonString);
void ParseInnerCmd(const JsonParserGeneratorRK::jsmntok_t *Token, String &CmdID);
bool AppliesToMe(String &Target);

void ParseMode(String JsonString, Mode *ModeToUpdate);
void ParseMode(const JsonParserGeneratorRK::jsmntok_t *Token, Mode *ModeToUpdate);

void ParseSettings(String JsonString, Settings *SettingsToUpdate);
void ParseSettings(const JsonParserGeneratorRK::jsmntok_t *Token, Settings *SettingsToUpdate);

void ParseRepeater(String JsonString, Repeater *RepeaterToUpdate);
void ParseRepeater(const JsonParserGeneratorRK::jsmntok_t *Token, Repeater *RepeaterToUpdate);

void ParseSequencer(const JsonParserGeneratorRK::jsmntok_t *Token, Sequencer *SequencerToUpdate, bool Add);

#endif