# DotStar Swarm Lighting
Lighting objects made with "DotStar" LEDs which communicate with each other in a swarm.

## Concept and Background
This project was started with a desire to make a high-visual-impact decorations for use in public displays. The core component in all the display objects is the DotStar LED. DotStar is a name used by Adafruit for independently-addressable RBG LEDs using the APA102 chipset (2-wire SPI interface). A public display can have multiple DotStar objects which can be manipulated from a central controller over WiFi.

Why create this stuff? The inspiration came from a giant, 50+ foot-tall oak tree in my front yard. I want to decorate for the holidays but this tree is so massive it doesn't make sense to run strands of "twinkle" lights up into the tree. Twinkle lights are prone to burn-outs, you would need a hundred strands to make a visual impact in such a large tree, and as the tree grows the strands would need repositioned if wrapped around the trunk or branches. To start this idea, I first designed the "DotStar Ball" which was a fairly large, bright sphere of individually-addressable LEDs. The ball size I thought would have a proportionally large visual impact when compared to an ornament on say a standard-sized christmas tree. But one sphere in a large tree is not enough. So the idea was that I would make 10-20 of these balls and to add to the "cool-factor", they would need to have animations and be able to coordinate the animations amongst themselves or respond to external input.

## Major Project Components
There are numerous components to the project including:
- lighting objects (sphere, garland, etc.),

**_Not Yet Implemented_**
- local swarm controller (device on the swarm network that sends commands to objects),
- external swarm controller (server or cloud app where you can build animations and send them to the local controller or objects).

## Elements with Documentation

- [Communication Structure](/CommunicationStructure.md)
- [The DotStar Ball](/DotStarBall/Readme.md)


