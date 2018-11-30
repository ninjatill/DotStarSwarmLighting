# Communication Structure
Messages are send to the DS swarm (DSS) devices using JSON. The JSON object has 3 distinct containers that are used by the DSS: root, target, and command. Each command contains parameters which govern device behavior or animations. One JSON string could have multiple targets, each containing multiple commands, each containing multiple parameters. The JSON format is:

Basic single-command:
```
{                                     //root object start
  "[target id]": {                    //target 1 object start
    "command type": {                 //command 1 object start
      "[param type]":[param value],
      "[param type]":[param value],
      "[param type]":[param value],
    }                                 //command 1 object close
  },                                  //target 1 object close
  
  "[target id]": {                    //target n object start
    "command type": {                 //command 1 object start
      "[param type]":[param value],
      "[param type]":[param value],
      "[param type]":[param value],
    }                                //command 1 object close
  }                                  //target n object close
}                                    //root object close

```

Basic sequence command:
```
{                                     //root object start
  "[target id]": {                    //target object start
    "sequnce command type": [         //sequence array start
      { "[command type]": {           //command object 1 start
        "[param type]":[param value],
        "[param type]":[param value],
        "[param type]":[param value],
      },                              //command object 1 end
      { "[command type]": {           //command object n start
        "[param type]":[param value],
        "[param type]":[param value],
        "[param type]":[param value],
      }                               //command object n start
    ]                                 //sequence array end
  }                                   //target object close
}                                     //root object close

```

With a basic command, as shown above, you can target multiple swarms and each command contained within will be executed immediately. With a basic sequence command, as shown above, you can also target multiple swarms but each command contained in the sequcne array, is loaded into memory on the device. Depending on the type of sequnce command (see Command Types below), the sequnce may or may not execute immediately.

## Targets
Each DSS device is assigned a "Swarm ID" (SID) which is a string of alphanumeric characters. Each character in the SID denotes a sub-grouping of devices. Currently only 3 characters are used: `"[major swarm group][horizontal group][vertical group]"`. If future functionality requires it, the code is flexible enough to easily add additional characters for more sub-groupings.
- For example, imagine multiple DSS devices in a tree. If you wanted to run an animation where the devices rapidly lit from bottom to top, you could group all the devices in the tree by assinging them to major swarm group "A". In this scenario, the horizontal grouping is inconsequential so you could use the wildcard character "-". And for the vertical grouping, the bottom most device would be in vertical group "A", next device up would be in vertical group "B", next device up would be in veritical group "C", etc. When you design the animation you would send an "all on" mode command to each SID with a slightly larger delay parameter for each. Example SIDs: `"A-A"`, `"A-B"`, `"A-C"`. See the example "Sequential Rapid Lighting" for a working example.
- To expand on the example above, if you had multiple trees in your yard and wanted to rapidly light those trees in sequence, then the devices in each tree would be assigned a different major swarm group. To target the first tree use `"A--"`, second tree `"B--"`, etc.

```txt
            Tree 1                     Tree 2

H  E |       ***           H  E |       ***
o    |    **     **        o    |    **     **
r  D |   *         *       r  D |   *         *
i    |   *         *       i    |   *         *
z  C |    **     **        z  C |    **     ** 
     |      |   |               |      |   |
G  B |      |   |          G  B |      |   |
r    |      |   |          r    |      |   |
p  A |     /     \         p  A |     /     \
     __________________         __________________
        A  B  C  D  E              A  B  C  D  E
	
       Vertical Group             Vertical Group

       Major Group A               Major Group B
```

## Command Types
When sent individually, these are referred to as a "command". When sent as part of a sequence, then it is a "command element".
- "M" - Mode commands contain parameters for setting up and running an animation.
- "R" - Repeater element. *Can only be used as a sequence command element.* The repeater tells the sequence to repeat the last x number of command elements, y times.
- "S" - Settings update command. Updates devices settings such as global brightness, time zone offset, etc.
- "X" - Execute command. Modes have a "wait to execute" flag that makes the mode wait for an "execute command" before processing. 
  - The execute command was envisioned as a way to coordinate the start of an sequence/mode/animation to account for processing or message propogation delays. Also, imagine a public display where a user could press a button, or send a text, etc. to start either a mode or sequence; an external device or server will send the execute command when that user input is received.

#### Sequence Commands
- "Q" - A self-contained sequence command. Enclosed command elements will replace any pre-existing sequence and the sequence will immedately start processing.
- "QS" - Contains the first part of a new multi-message sequence. A new sequence is created and then waits for additional messages which add on to the sequence. The sequence will not process until a "QE" command is received.
- "QA" - Contains additional elements to add onto a multi-message sequence command. Can be used to add onto a already processing "Q" command. Does not start the sequence processing. If the sequence was already processing, the sequence will continue to process.
- "QE" - Contains the final/end elements to add onto a multi-message sequence command. The sequence will begin processing after a "QE" command finishes parsing.

## Parameter Types
There are 2 types of parameters: required, and mode-specific. Required parameters are required for every mode command sent. Mode-specific parameters, as the name implies, are optional parameters that a mode uses to tailor the animation. Parameter types are always wrapped in double-quotation marks. For parameter values:
- if it is a string, the it must be wrapped in double-quotation marks,
- if it is a number, then the number is sent as-is without wrapping quotation marks,
- if it is a boolean, then the value should be true or false without any wrapping quotation marks.

### Parameters Explained
Parameter list is in format: 
- `"[Param Char]" - [Param Name] - [Param Datatype]`
  - Animation description.
  - Important notes. (optional)
  - Values: (optional)
  - Example:

### Mode Parameters
#### Required Parameters
These parameters must always be specified. The mode will not display if they are omitted.
- "D" - Duration - unsigned long
  - Secifies the duration of the animation in miliseconds.
  - Example: `"U":5000` for 5000 miliseconds (5 seconds) total duration of the animation.
- "M" - Mode ID Number = uint8_t
  - Specifies the mode id number and associated animation to process.
  - Example `"M":11` for mode number 11 (fade).
- "T" - Steps - unsigned long
  - Specifies the number of steps in the animation and must be greater than 0.
  - Example `"T":5` for 5 total steps in animation.
  
Note: Duration (D) is divided by Steps (T) to calculate the refresh rate of the animation. For example, if you specify a duration of 1000 (1 second) and 10 steps, the animation will advance/process every 100 miliseconds (1000/10 = 100). The calculation is approximate because there is an estimated overhead of approximately 12 miliseconds between each refresh. The actual duration may be +/- several miliseconds. 

#### Optional Parameters
- "A" - Advance Color On - int
  - Specifies when to advance to the next color in the color array.
  - Values: 1 = on step advance, 2 = repeat advance.
- "C" - Color Array - Array of uint32_t
  - An array of colors to use. Colors are 32-bit integers but only the right-most 3 bytes are used to specify single-byte Red, Green and Blue values. It is best to convert RGB hexidecimal values to base10 decimals. For example, 0xFF0000 (red in hex) = 16711680 (red in base10).
  - To step through the color array, you must specify the "A" parameter. If no colors are specified, black (off) is assumed.
  - Example: `"C":[0,255,16777215]` for Black (off), Blue, White
- "D" - Start Delay - unsigned long
  - Number of miliseconds to delay before starting the animation. Delay can be used to coordinate "moving sequences" across members of the swarm.
  - Example: `"D":20` for a 20 milisecond delay before starting command.
- "F" - Fade Size - int
  - Number of elements to fade in animations such as spin, twinkle, rain, etc.
- "H" - Width - int
  - Specifies the width of an animation. Has different meaning depending on the animation; see animation description.
  - Example: `"H":5`
- "I" - Direction of Animation - uint8_t
  - Used for directional animations (spin, fill, etc.) to specify the direction of advance (when viewed from above). 
  - Values: 0 = CW/Up, 1 = CCW/Down, 2 = CW reverse on Step, 3 = CCW reverse on Step, 4 = CW reverse on Repeat, 5 = CCW reverse on Repeat, ... 254 = Randomize
  - Example: `"I":1` for Counter-Clockwise/Down direction.
- "L" - Tail Size - int
  - Size of the tail of the animation. ?!? needed ?!?
- "O" - Object Array - Array of Strings
  - An object can be a column (C) or row (R) of pixels or a single pixel (P). To explicity address all pixels, use "A" with any index (i.e. "A0"). String format should be `"[char for obj type][uint_16 for obj index]"`. The object index is zero-based.
  - Example: `"O":["C20","R8","P55"]` for Column 20, Row 8 and Pixel 55.
- "R" - Time to Repeat - int
  - Number of times to repeat the mode/animation. Use the max negative value of -2,147,483,648 for indefinite repeat. Use other negative values to specify a random repeat value.
  - Example: `"R":50` for reapeat 50 times. Note, this will display the mode 51 times since he first run does not count towards the repeat count.
  - Example: `"R":-500` to repeat a random number of times up to 500.
- "W" - Color Wheel Speed - uint8_t
  - If specified, the animiation will use a color wheel algorithm to step through the colors of the rainbow. The value governs the speed of the color transitions. Lower values will change slower than larger values.
  - Example: `"W":3` for color wheel enabled with a +/- 3-bit change on each color wheel advance.
- "X" - Wait for Execution - bool
  - Forces the mode to wait for an "execution" command before running the animation. This is designed to help coordinate timing / processing delays amongst the swarm.
  - Example: `"X":true` to set the wait for execution flag.

### Settings Parameters
- "B" - Global Brighness - uint8_t
  - Use to lower the overall brightness level of the swarm devices. 0 = 0%, 255 = 100%. The DotStar LED are intensely bright, so on a dark night without moonlight, you may want to lower the overall brightness to stave off neighbor complaints. 
- "D" - Debug Level - uint8_t
  - Changes the logging filter level for messages sent to the serial console and off-site log collection services.
- "I" - Multicast IP Address - Array[4] of uint8_t
  - Changes the Multicast IP Address the device listens for.
- "O" - Timezone Offset (from UTC) - int8_t
  - Used to change the timezone offset. Local time appears on some log messages and status reports.
- "P" - UDP Port - uint16_t
  - Changes the UDP port the device listens on. When changed, the device will re-initialize UDP.
- "T" - Daylight Saving Time Enable - bool
  - Enables (true) or Diables (false) daylight savings time. Time appears on some log messages and status reports.

## Creating A DS Swarm Command
1. First, create the root JSON container: `{}`
2. Next, target a swarm ID using a JSON object:  `{"A--":{}}`. The "A--" targets swarm "A", and has wildcards for the horizontal and vertical groupings. Therefore, every device in swarm "A" will respond to this command.
3. Next, 

## Command Examples

#### Settings Updates
- `{"A--":{"S":{"B":128,"O":-5,"T":true,"I":[239,1,1,240]}}}`
  - Targets SID "A--", brightness to 128 (50%), timezone offset to -5 (Eastern Standard Time), enables DST, multicast IP address to 239.1.1.240.

#### Basic Commands
- All On - `{"ABC":{"M":{"M":2,"U":5000,"T":1,"C":[16277215]}}}`
  - Sets devices with SID "ABC" to color white for a duration of 5 seconds. However, since there is no repeat command, the device will turn off (set color black) by itself. You must followup with an off command such as `{"ABC":{"M":{"M":2,"U":5000,"T":1,"C":[0]}}}`

- Blink - `{"A--":{"M":{"M":2,"U":5000,"T":2,"C":[255,0],"A":0,"R":50}}}`
  - Sets devices with SID "A--" to blue for 2.5 seconds and then off for 2.5 seconds. Repeats this 50 more times.

- Rapid Sequential Lighting (Vertical) - `{"A-A":{"M":{"M":2,"U":1000,"T":1,"C":[255]}}, "A-B":{"M":{"M":2,"U":1000,"T":1,"C":[255],"D":200}}, "A-C":{"M":{"M":2,"U":1000,"T":1,"C":[255],"D":400}}, "A-D":{"M":{"M":2,"U":1000,"T":1,"C":[255],"D":600}}, "A-E":{"M":{"M":2,"U":1000,"T":1,"C":[255],"D":800}}}`
  - Assuming you have a swarm with 5 vertical groups where group A is lowest and group E is highest: Turn on each vertical group from A to E with a 200 milisecond delay between each group lighting.

- Fade - `{"B--":{"M":{"M":11,"U":5000,"T":100,"C":[0,13320948],"O":["C0","C5","C11","C17","C23"]}}}`
  - Targets SID "B--" and fades 6 columns from off to purple in 5 seconds with 100 transition steps.

- Pulse - `{"B--":{"M":{"M":11,"U":5000,"T":100,"C":[0,13320948],"O":["C0","C5","C11","C17","C23"],"R":1,"A":1}}}`
  - Targets SID "B--" and faces 6 columns from off to purple in 5 seconds with 100 transition steps. Then immediately fades from purple back to off.

- Twinkle - `{"---":{"M":12,"U":1000,"T":5,"C":[16777215,0],"O":["P0"],"I":254,"H":110,"R":21600}}}`
  - Targest SID "---" (all devices in all swarms) and randomly lights 20% of the pixels to white. Every 200 miliseconds the first 20% turn off and the next random 20% turn on.

- Spin

#### Sequences
- Basic Sequence

- With Repeaters

- Rapid Sequential Lighting with Re-Synch on Next Mode
