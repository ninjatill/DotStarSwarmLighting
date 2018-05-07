# DotStarSwarmLighting
Lighting objects made with "DotStar" LEDs which communicate with each other in a swarm.

## Concept and Background
This project was started with a desire to make a high-visual-impact decorations for use in public displays. The core component in all the display objects is the DotStar LED. DotStar is a name used by Adafruit for independently-addressable RBG LEDs using the APA102 chipset (2-wire SPI interface).

Why create this stuff? The inspiration came from a giant, 50+ foot-tall oak tree in my front yard. I want to decorate for the holidays but this tree is so massive it doesn't make sense to run strands of "twinkle" lights up into the tree. Twinkle lights are prone to burn-outs, you would need a hundred strands to make a visual impact in such a large tree, and as the tree grows the strands would need repositioned if wrapped around the trunk or branches. And so I first designed the "DotStar Sphere" which was a large, bright sphere of individually-addressable LEDs which would have proportionally large visual impact when compared to an ornament on say a standard-sized christmas tree. But one sphere in a large tree is not enough. So the though was that I would make 10-20 of these spheres and to add to the "cool-factor", they would need to have animations and be able to coordinate the animations amongst themselves.

## Major Project Components
There are numerous components to the project including:
1. lighting objects (sphere, garland, etc.),
2. local swarm controller (device on the swarm network that sends commands to objects),
3. configurator (server or cloud app where you can build animations and send them to the controller or objects).

### Object - DotStar Sphere
