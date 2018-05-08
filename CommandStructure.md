# Command Structure
Commands are send to the DS swarm (DSS) devices using JSON. The JSON object has 3 distinct containers that are used by the DSS: target, command and parameters. One JSON string could have multiple targets, each containing multiple commands, each containing multiple parameters. The JSON format is:

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
Each DSS device is assigned a "Swarm ID" (SID) which is a string of alphanumeric characters. Each character in the SID denotes a sub-grouping of devices. Currently only 3 characters are used: `[major swarm group][horizontal group][vertical group]`. If future functionality requires it, the code is flexible enough to easily add additional characters for more sub-groupings.
- For example, imagine multiple DSS devices in a tree. If you wanted to run an animation where the devices rapidly lit from bottom to top, you could group all the devices in the tree by assinging them to major swarm group "A". In this scenario, the horizontal grouping is inconsequential so you could use the wildcard character "-". And for the vertical grouping, the bottom most device would be in vertical group "A", next device up would be in vertical group "B", next device up would be in veritical group "C", etc. When you design the animation you would send an "all on" mode command to each SID with a slightly larger delay parameter for each. Example SIDs: `"A-A"`, `"A-B"`, `"A-C"`. See the example "Sequential Rapid Lighting" for a working example.
- To expand on the example above, if you had multiple trees in your yard and wanted to rapidly light those trees in sequence, then the devices in each tree would be assigned a different major swarm group. To target the first tree use `"A--"`, second tree `"B--"`, etc.

## Command Types
- "M" - Mode commands contain parameters for setting up and running an animation.
- "Q" - A self-contained sequence command. Will immedately start running the sequence.
- "QS" - Contains the first part of a new sequence. A new sequence is created and then waits for additional messages which add on to the sequence. The sequence will not process until a "QE" command is received.
- "QA" - Contains additional elements to add onto a multi-message sequence command. 
- "QE" - Contains the final/end elements to add onto a multi-message sequence command. The sequence will begin processing after a "QE" command finishes parsing.
- "S" - Settings update command. Updates devices settings such as global brightness, time zone offset, etc.
- "X" - Execute command. Modes have a "wait to execute" flag that makes the mode wait for an "execute command" before processing. 
  - The execute command was envisioned as a way to coordinate the start of an sequence/mode/animation to account for processing or messaage propogation delays. Also, imagine a public display where a user could press a button, or send a text, etc. to start either a mode or sequence; an external device or server will send the execute command when that user input is received.

## Parameter Types
There are 2 types of parameters: universal, and mode-specific. Universal parameters are required for every command sent. Mode-specific parameters, as the name implies, are optional parameters that a mode uses to tailor the animation.

#### Mode Parameters
Universal Parameters
- "U"

## Creating A DS Swarm Command
1. First, create the root JSON container: `{}`
2. Next, target a swarm ID using a JSON object:  `{"A--":{}}`. The "A--" targets swarm "A", and has wildcards for the horizontal and vertical groupings. Therefore, every device in swarm "A" will respond to this command.
3. Next, 
