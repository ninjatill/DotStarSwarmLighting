

#include "application.h"
#include "CmdProcessorv2.h"
#include "Settings.h"
#include "Mode.h"
#include "Repeater.h"
//#include "Sequencer.h"
//#include <string>

// This #include statement was automatically added by the Particle IDE.
#include "JsonParserGeneratorRK.h"

//char msg_cp[255] = "";
JsonParserStatic<2000, 250> jparser; //2000 is oversized to accomodate a minium Network MTU of 1500 with a token every ~8 bytes.

void ParseNew(char *NewCmd) 
{
    //bool error = false;
    jparser.clear();
	jparser.addString(NewCmd);
	if (!jparser.parse()) {
		Log.error("JSON parse failed. Check your format.");
        Log.error("Cmd Txt: %s", NewCmd);
        return;
	}
	
	for (int i=0; i<32; i++) {
    	const JsonParserGeneratorRK::jsmntok_t *targetKeyTok;
    	const JsonParserGeneratorRK::jsmntok_t *targetValueTok;
    	
    	String targetKeyName;
    	size_t targetKeyLen;
    	
	    if (jparser.getKeyValueTokenByIndex(jparser.getOuterObject(), targetKeyTok, targetValueTok, i)) {
	        if (jparser.getTokenValue(targetKeyTok, targetKeyName)) {
	             Log.info("(%i) New cmd targets device/group: %s", i, targetKeyName.c_str());
	            
	            if (AppliesToMe(targetKeyName)) {
	                if (targetValueTok->type == 1) {
	                    //Command is a JSON object, parse it.
                    	const JsonParserGeneratorRK::jsmntok_t *cmdKeyTok;
                    	const JsonParserGeneratorRK::jsmntok_t *cmdValueTok;
                    	
                    	String cmdKeyName;
                    	size_t cmdKeyLen;
	                    
	                    for (int j=0; j<32; j++) {
	                        if (jparser.getKeyValueTokenByIndex(targetValueTok, cmdKeyTok, cmdValueTok, j)) {
	                            if (jparser.getTokenValue(cmdKeyTok, cmdKeyName)) {
	                                
	                                ParseInnerCmd(cmdValueTok, cmdKeyName);
	                            
	                            } else {
	                                Log.error("Cannot parse command ID.");
	                                //error = true;
	                            }
	                        } else {
	                            //Log.error("Cannot parse cmd object %i or end of list.", j);
	                            //error = true;
	                            break;
	                        }
	                    }
	                } else {
	                    Log.error("Command index %i does not contain a JSON object.", i);
	                    //error = true;
	                }
	            }
	        } else {
	            Log.error("Cannot get device target ID for command index %i.", i);
	            //error = true;
	        }
	    } else {
	        //Log.error("Cannot parse target object %i or end of objects.", i);
	        //error = true;
	        break;
	    }
	}
    //} //for (auto id : root)
} //ParseNew

String CmdElementType(String *JsonString) {
    char json[255];
    (*JsonString).toCharArray(json, 255);
    return CmdElementType(json);
}

String CmdElementType(char *JsonString) 
{
    jparser.clear();
	jparser.addString(JsonString);
	if (!jparser.parse()) {
		Log.error("JSON parse failed for inner cmd (string). Check your format.");
        Log.error("Cmd Txt: %s", JsonString);
        return "";
	}
	
	const JsonParserGeneratorRK::jsmntok_t *targetKeyTok;
	const JsonParserGeneratorRK::jsmntok_t *targetValueTok;
	
	String targetKeyName;
	size_t targetKeyLen;
	
    if (jparser.getKeyValueTokenByIndex(jparser.getOuterObject(), targetKeyTok, targetValueTok, 0)) {
        if (jparser.getTokenValue(targetKeyTok, targetKeyName)) {
            return targetKeyName;
        }
    }
}

void ParseInnerCmd(const JsonParserGeneratorRK::jsmntok_t *Token, String &CmdID) 
{
    if (strcmp(CmdID,"M") == 0) {    // Mode Command.
        Log.info("Parsing Mode command...");
        //if (s_cp->Debug) { Serial.print("Parsing mode cmd:"); }
        ParseMode(Token, &mo);
        //return;
    } else if (strcmp(CmdID,"Q") == 0) {    // Sequence Command
        Log.info("Parsing FULL sequence command...");
        //A full sequence sent in a single message.
        //Create a new sequence, add encapsulated elements to new sequence, mark sequence active.
        
        ParseSequencer(Token, &sq, false);
        sq.Active = true;
        sq.AdvanceNow = true;
        return;
    } else if (strcmp(CmdID,"QS") == 0) {
        Log.info("Parsing sequence start command...");
        //Start of a multi-element sequence sent a few elements at a time.
        //Create a new sequence, add encapsulated elements to new sequence, 
        //do not mark active because we are waiting to add additional inbound elements in subsequent messges.
        ParseSequencer(Token, &sq, false);
        return;
    } else if (strcmp(CmdID,"QA") == 0) {
        Log.info("Parsing sequence add command...");
        //Add encapsulated elements to current sequence.
        ParseSequencer(Token, &sq, true);
        return;
    } else if (strcmp(CmdID,"QE") == 0) {
        Log.info("Parsing sequence end command...");
        //End of a multi-message sequence build.
        //Add encapsulated elements to current sequence, mark sequence active.
        ParseSequencer(Token, &sq, true);
        sq.Active = true;
        sq.AdvanceNow = true;
        return;
    } else if (strcmp(CmdID,"S") == 0) {
        Log.info("Parsing settings cmd...");
        ParseSettings(Token, &s);
        return;
    } else if (strcmp(CmdID,"X") == 0) {
        Log.info("Parsing execute cmd...");
        mo.WaitToExec = false;
        mo.UpdateLastRun(true);
        return;
        
    } else {
        Log.error("Unrecognized command ID: %s", CmdID);
        //error = true;
    }
}

bool AppliesToMe(String &Target) 
{
    //If the target device key is large, then it is a device ID, not a swarm ID.
    if (Target.length() > 10) {
        Log.info("Target is a device ID: %s", Target.c_str());
        if ( Target.equals(System.deviceID()) ) {
            Log.warn("!!!Cmd applies to me!!!");
            return true;
        } else {
            Log.warn("...Cmd does not apply to me...");
            return false;
        }
    }
    
    Log.info("Target is a swarm ID: %s", Target.c_str());
    
    char I = Target[0];
    char H = Target[1];
    char V = Target[2];
    
    bool a[3] = {false, false, false};
    
    //Breaking out each ID comparison for debugging.
    if ( (I == s.SwarmID) || I == '-' ) {
        //if (s_cp->Debug) { Serial.println("...Swarm ID Match"); }
        Log.trace("...Swarm ID Match: %c", I);
        a[0] = true;
    }
    
    if ( (H == s.HGroup) || H == '-' ) {
        //if (s_cp->Debug) { Serial.println("...Horiz Group Match"); }
        Log.trace("...Horiz Group Match: %c", H);
        a[1] = true;
    }
    
    if ( (V == s.VGroup) || V == '-' ) {
        //if (s_cp->Debug) { Serial.println("...Vert Group Match"); }
        Log.trace("...Vert Group Match: %c", V);
        a[2] = true;
    }
    
    if ( a[0] && a[1] && a[2] ) {
        //if (s_cp->Debug) { Serial.println("!!!Cmd applies to me!!!"); }
        Log.warn("!!!Cmd applies to me!!!");
        return true;
    } 
    
    //if (s_cp->Debug) { Serial.println("...Cmd does not apply to me..."); }
    Log.warn("...Cmd does not apply to me...");
    return false;
}

void ParseMode(String JsonString, Mode *ModeToUpdate) 
{
    jparser.clear();
	jparser.addString(JsonString);
	if (!jparser.parse()) {
		Log.error("JSON parse failed for mode (string). Check your format.");
        Log.error("Cmd Txt: %s", JsonString);
        return;
	}
	
	const JsonParserGeneratorRK::jsmntok_t *targetKeyTok;
	const JsonParserGeneratorRK::jsmntok_t *targetValueTok;
	
	String targetKeyName;
	size_t targetKeyLen;
	
    if (jparser.getKeyValueTokenByIndex(jparser.getOuterObject(), targetKeyTok, targetValueTok, 0)) {
        if (jparser.getTokenValue(targetKeyTok, targetKeyName)) {
            ParseMode(targetValueTok, ModeToUpdate);
        }
    }
}

void ParseMode(const JsonParserGeneratorRK::jsmntok_t *Token, Mode *ModeToUpdate) 
{
    Log.trace("ParseMode (obj); pre-parse free memory: %i", System.freeMemory());

    Mode mode = Mode();
    bool valid[] = {false, false};
    
    int intValue;
    String strValue;
    bool boolValue;
    unsigned long longValue;

    const JsonParserGeneratorRK::jsmntok_t *valueTok;
    
	if (jparser.getValueTokenByKey(Token, "M", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
		    mode.ID = intValue;
	    } else {
	        Log.error("...Cannot parse mode param (M).");
	    }
	}

    if (jparser.getValueTokenByKey(Token, "A", valueTok)) {
        if (jparser.getTokenValue(valueTok, intValue)) {
            mode.AdvanceColorOn = intValue;
        } else {
            Log.error("...Cannot parse mode param (A).");
        }
	}
	
	if (jparser.getValueTokenByKey(Token, "D", valueTok)) {
	    if (jparser.getTokenValue(valueTok, longValue)) {
	        mode.Delay = longValue;   
	    } else {
	        Log.error("...Cannot parse mode param (D).");
	    }
	}
	
	if (jparser.getValueTokenByKey(Token, "H", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
	        mode.Width = intValue;   
	    } else {
	        Log.error("...Cannot parse mode param (H).");
	    }
	}
    
    if (jparser.getValueTokenByKey(Token, "R", valueTok)) {
        if (jparser.getTokenValue(valueTok, intValue)) {
            mode.Repeat = intValue;
        } else {
            Log.error("...Cannot parse mode param (R)."); 
        }
		
	}
	
	if (jparser.getValueTokenByKey(Token, "T", valueTok)) {
	    if (jparser.getTokenValue(valueTok, longValue)) {
	        mode.Steps = longValue;
    		if (mode.Steps > 0) {
                valid[1] = true;
            }
	    } else {
	        Log.error("...Cannot parse mode param (T).");
	    }
		
	}

    if (jparser.getValueTokenByKey(Token, "U", valueTok)) {
        if (jparser.getTokenValue(valueTok, longValue)) {
            mode.Duration = longValue;
    		if (mode.Duration > 0) {
                valid[0] = true;
            }
        } else {
            Log.error("...Cannot parse mode param (U).");
        }
	}
	
	if (jparser.getValueTokenByKey(Token, "W", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
	        mode.ColorWheelSpeed = intValue;   
	    } else {
	        Log.error("...Cannot parse mode param (W).");
	    }
	}
	
	if (jparser.getValueTokenByKey(Token, "X", valueTok)) {
	    if (jparser.getTokenValue(valueTok, boolValue)) {
	        mode.WaitToExec = boolValue;   
	    } else {
	        Log.error("...Cannot parse mode param (X).");
	    }
	}
    
	int count = 0;
	if (jparser.getValueTokenByKey(Token, "C", valueTok)) {
	    if (valueTok->type == 2) {
	        intValue = jparser.getArraySize(valueTok);
    	    for (int i=0; i<intValue && i<arraySize(mode.Colors); i++) {
    	        if (jparser.getValueByIndex(valueTok, i, longValue)) {
    	            mode.Colors[i] = longValue;
    	            count++;
    	        } else {
    	            Log.error("...Cannot parse color (i).");
    	        }
    	    }
    	    mode.ColorCount = count;
    	    Log.trace("...Colors Found (%i).", mode.ColorCount);
	    } else {
	        Log.error("...Colors found, but not array!");
	    }
	} else {
	    Log.trace("...No colors in cmd.");
	}
	
	count = 0;
	if (jparser.getValueTokenByKey(Token, "O", valueTok)) {
	    if (valueTok->type == 2) {
	        intValue = jparser.getArraySize(valueTok);
    	    for (int i=0; i<intValue && i<arraySize(mode.Objects); i++) {
                if (jparser.getValueByIndex(valueTok, i, strValue)) {
                    mode.Objects[i] = strValue;
                    count++; 
                } else {
                    Log.error("...Cannot parse object (i).");
                }
    	    }
    	    mode.ObjectCount = count;
    	    Log.trace("...Objects Found (%i).", mode.ObjectCount);
	    } else {
	        Log.error("...Objects found, but not array!");
	    }
	    
	} else {
	    Log.trace("...No objects in cmd.");
	}

    bool modeIsValid = true;
    for (int i=0; i<arraySize(valid); i++) {
        if (!valid[i]) { modeIsValid = false; }
    }
    
    if (modeIsValid) {
        mode.Complete = false;
        mode.UpdateLastRun(true);
        *ModeToUpdate = mode;
    }
    else {
        Log.error("Mode command has missing required elements! Cannot execute.");
    }
    
    Log.trace(mode.ToString());
    Log.trace(mode.AnimationVariables());
    Log.trace("ParseMode (obj); post-parse free memory: %i", System.freeMemory());
}

//****************************************************************************************************
//The global settings are updated rather than replaced.
//It is more likely that a user would want to update a single setting rather than a wholesale
//replacement (i.e. adjusting the global brightness without editing the UDP settings.)
//****************************************************************************************************
void ParseSettings(String JsonString, Settings *SettingsToUpdate) 
{
    jparser.clear();
	jparser.addString(JsonString);
	if (!jparser.parse()) {
		Log.error("JSON parse failed for settings (string). Check your format.");
        Log.error("Cmd Txt: %s", JsonString);
        return;
	}
	
	const JsonParserGeneratorRK::jsmntok_t *targetKeyTok;
	const JsonParserGeneratorRK::jsmntok_t *targetValueTok;
	
	String targetKeyName;
	size_t targetKeyLen;
	
    if (jparser.getKeyValueTokenByIndex(jparser.getOuterObject(), targetKeyTok, targetValueTok, 0)) {
        if (jparser.getTokenValue(targetKeyTok, targetKeyName)) {
            ParseSettings(targetValueTok, SettingsToUpdate);
        }
    }
}

void ParseSettings(const JsonParserGeneratorRK::jsmntok_t *Token, Settings *SettingsToUpdate) 
{
    int intValue;
    String strValue;
    bool boolValue;
    unsigned long longValue;
    
    const JsonParserGeneratorRK::jsmntok_t *valueTok;
    
    if (jparser.getValueTokenByKey(Token, "B", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		SettingsToUpdate->GBright = intValue;
		} else {
		    Log.error("Could not parse setting (B).");
		}
	}
    
	if (jparser.getValueTokenByKey(Token, "D", valueTok)) {
	    if (jparser.getTokenValue(valueTok, boolValue)) {
    		SettingsToUpdate->Debug = boolValue;
    		
    		if (SettingsToUpdate->Debug) {
    		    Log.warn("Debugging messages enabled.");
    		} else {
    		    Log.warn("Debugging messages disabled.");
    		}
		} else {
		    Log.error("Could not parse setting (D).");
		}
	}
	
	if (jparser.getValueTokenByKey(Token, "O", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		SettingsToUpdate->TimeZoneOffset = intValue;
    		Resets[1] = true;
		} else {
		    Log.error("Could not parse setting (O).");
		}
	}
	
	if (jparser.getValueTokenByKey(Token, "P", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		SettingsToUpdate->UDPPort = intValue;
    		Resets[2] = true;
		} else {
		    Log.error("Could not parse setting (P).");
		}
	}
	
	if (jparser.getValueTokenByKey(Token, "S", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		SettingsToUpdate->UDPMaxPacketSize = intValue;
    		Resets[2] = true;
		} else {
		    Log.error("Could not parse setting (S).");
		}
	}
	
	if (jparser.getValueTokenByKey(Token, "T", valueTok)) {
	    if (jparser.getTokenValue(valueTok, boolValue)) {
    		SettingsToUpdate->EnableDST = boolValue;
    		Resets[1] = true;
		} else {
		    Log.error("Could not parse setting (T).");
		}
	}

    Log.trace(SettingsToUpdate->ToString());
}

//****************************************************************************************************
//The repeater element is used by the sequencer.
//****************************************************************************************************
void ParseRepeater(String JsonString, Repeater *RepeaterToUpdate) 
{
    jparser.clear();
	jparser.addString(JsonString);
	if (!jparser.parse()) {
		Log.error("JSON parse failed for repeater (string). Check your format.");
        Log.error("Cmd Txt: %s", JsonString);
        return;
	}
	
	const JsonParserGeneratorRK::jsmntok_t *targetKeyTok;
	const JsonParserGeneratorRK::jsmntok_t *targetValueTok;
	
	String targetKeyName;
	size_t targetKeyLen;
	
    if (jparser.getKeyValueTokenByIndex(jparser.getOuterObject(), targetKeyTok, targetValueTok, 0)) {
        if (jparser.getTokenValue(targetKeyTok, targetKeyName)) {
            ParseRepeater(targetValueTok, RepeaterToUpdate);
        }
    }
}

void ParseRepeater(const JsonParserGeneratorRK::jsmntok_t *Token, Repeater *RepeaterToUpdate) 
{
    Repeater rep;
    bool valid[2] = {false, false};  //Used to test if the element is valid. Must have Repeat count.
    
    int intValue;
    const JsonParserGeneratorRK::jsmntok_t *valueTok;
    
    if (jparser.getValueTokenByKey(Token, "R", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		rep.RepeatLoops = intValue;
    		valid[0] = true;
		} else {
		    Log.error("Could not parse parameter (R).");
		}
	}
	
    if (jparser.getValueTokenByKey(Token, "T", valueTok)) {
	    if (jparser.getTokenValue(valueTok, intValue)) {
    		rep.StepsToRepeat = intValue;
    		valid[1] = true;
		} else {
		    Log.error("Could not parse parameter (T).");
		}
	}
	
    bool isValid = true;
    for (int i=0; i<arraySize(valid); i++) {
        if (!valid[i]) { isValid = false; }
    }
    
    if (isValid) {
        *RepeaterToUpdate = rep;
    }
    else {
        Log.error("Repeater command has missing required elements! Cannot execute.");
    }
}

//****************************************************************************************************
//A sequencer consists of an array of command elements such as a mode, setting or repeater.
//****************************************************************************************************
void ParseSequencer(const JsonParserGeneratorRK::jsmntok_t *Token, Sequencer *SequencerToUpdate, bool Add = false) 
{
    Log.trace("ParseSequencer (obj); pre-parse free memory: %i", System.freeMemory());
    Sequencer sq;
    int intValue;
    String strValue;
    const JsonParserGeneratorRK::jsmntok_t *valueTok;
    
    int count = 0;
    
    //Check if the token is an array.
    if (Token->type == 2) {
        intValue = jparser.getArraySize(Token); //Get the array size.

        //Loop through the array and add each object to the sequence.
	    for (int i=0; i<intValue; i++) {
	        if (jparser.getValueTokenByIndex(Token, i, valueTok)) {  //Get the token at the array index.
	            if (jparser.getTokenJsonString(valueTok, strValue)) {  //Get the token as a string.
    	            Log.trace("...Adding element to sequencer: %s", strValue.c_str());
    	            sq.Add(strValue);  //Add token string to sequencer.
    	            count++;
    	        } else {
    	            Log.trace("No element at index: %i. Breaking.", i);
    	            break;
    	        }
	        }
	    }
	    
	    Log.trace("Elements (%i) added to Sequence.", count);
	    *SequencerToUpdate = sq;  //Assign the new sequncer to desired memory location.
	    
	    Log.trace(SequencerToUpdate->ToString());
        
    } else {
        Log.error("Sequence is not a valid Json array.");
    }
    
}






