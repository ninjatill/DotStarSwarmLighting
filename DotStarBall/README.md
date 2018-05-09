# DotStar Ball (aka. DotStar Sphere)
The first object designed for this swarm ecosystem is the DotStar Ball (DSB). When I started designing this object, I used the some of these criteria:
- had to be large enough to have a visual impact hanging on a large tree branch,
- had to be (relatively) low cost since I had to make many of them,
- has to receive external commands and display animations from that input,
- has to be addressable individually or in groups.

#### Design Constraints
- Anything I create has to live outdoors. It has to be designed to operate in Northeastern US weather (snow, rain, high-winds, etc.)
- I knew I would be using DotStar LED strips. I used them for a previous project and found them easy to use and program. These strips optionally come with a silicone jacket with an IP67 rating which satisfies the weather issue. To keeps costs low and with a rough guestimate of the size of the sphere, I chose the version with 60 pixels/meter which would give me a pixel length of 16.67mm.
- I have a 3D printer so I knew that I would most-likely design and print a custom support structure to keep it light and low cost. I have an original Prusa i3 Mk2 printer with maximum print dimensions 250x200x180mm.
- I wanted the electronics to be accessible without completely disassembling the ball. Also, for best WiFi reception, the electronics should be located on the under-side of the ball.

## Roadmap (To Do Features) (In _Loose_ Order of Priority)
- Add firmware features (sleep, report status to controller, etc.)
- Finalize designs for electronics custom PCB, electronics housing and hanging bracket.
- Investigate using hardware timers to control animation processing intervals.
- Add temperature monitoring/fan control for the PSU.
- Add support for external hardware triggers.
- Add environmental monitoring hardware making each light a small weather station.
- Add support for [DMX-512](https://en.wikipedia.org/wiki/DMX512).
- Add support for [Light-O-Rama](http://www1.lightorama.com/) controllers.

## Bill of Materials
- [Particle Photon](https://www.particle.io/products/hardware/photon-wifi) ($20)
- 10 Meters of SK9822 or APA102 LEDs, 60 Pixels/Meter, Silicone-Jacketed (IP67), Black Flex PCB (~$10/meter) from [Adafruit](https://www.adafruit.com/product/2239), [AliExpress](https://www.aliexpress.com/item/1m-5m-APA102-Smart-led-pixel-strip-Black-White-PCB-24-36-60-96-leds-pixels/32322326979.html?spm=2114.search0104.3.8.18da31a9f5sv0u&ws_ab_test=searchweb0_0,searchweb201602_1_10152_10151_10065_10344_10068_10130_10324_10342_10547_10325_10343_10546_10340_5722611_10548_10341_10545_10696_5722911_5722811_10084_5722711_10083_10618_10307_5711211_10059_308_100031_10103_10624_10623_10622_10621_10620_5711311_5722511,searchweb201603_2,ppcSwitch_2&algo_expid=6ef3fe06-63bb-41f2-b8bc-39bc1ad5b3ed-1&algo_pvid=6ef3fe06-63bb-41f2-b8bc-39bc1ad5b3ed&priceBeautifyAB=0)
  - Reels of LEDs should come with extra 4-Pin JST connectors for connecting the electronics PCB to the LED strip.
- 3D-Printed Support Structure (~$48 for 2kg of PETG) (see the [readme](/DotStarBall/stl/readme.md) for more details.)
  - PETG 1.75mm Filament from [MakerGeeks](https://www.makergeeks.com/collections/maker-series-petg)
    - Choose appropriate filament for your 3D printer or have a 3D printing service manufacture the printed objects for you.
- 5V, 40A Switching Power Supply ($25) from [Amazon](https://www.amazon.com/ALITOVE-Transformer-Converter-Security-Computer/dp/B077SYHQCJ/ref=sr_1_2?ie=UTF8&qid=1525871493&sr=8-2&keywords=5v+40a+power+supply)
- 6 2-pin Power Connectors ($10) from [Amazon](https://www.amazon.com/TrendBox-Connector-Adapter-Electronics-Projects/dp/B0722SCRHM/ref=sr_1_1?s=electronics&ie=UTF8&qid=1525871615&sr=1-1&keywords=2pin+silicone)
- Multi-colored Hookup Wire (size appropriately and consider outdoor exposure when selecting)
- Silicone Caulking
- Solder
- 64+ #6 1/2" Stainless Steel Screws from [Fastener Mart](https://www.fastenermart.com/SC165-1452.html)
- 16+ #6 3/4" Stainless Steel Screws from [Fastener Mart](https://www.fastenermart.com/SC165-3452.html)

## Similar Designs
I mostly had the support structure designed and fabricated prior to doing any kind of search for a similar idea or concept. I did find a few similar designs out there but none that fit my exact requirements. Most were stand-alone objects and higher in cost to fabricate. Here's a brief comparison:
- [Spherical LED Matrix](http://www.instructables.com/id/Spherical-LED-Matrix-Sphere-Shaped-LED-Screen-From/) This project is most closely related to what I'm trying to do. The maker used a metal support structure and oriented the pixel strips in a horizontal manner (which I found to be an unfavorable design.) The maker hides the non-uniform LED positioning by enclosing the entire structure in a translucent shell.
  - This design differs from the DSB in that the DSB is smaller, lighter, and WiFi enabled. Both projects are similarly (proportionally) priced. Additionally, this design uses specialized hardware and uses non-wireless communication protocols/hardware such as USB or DMX-512. It is not addressable in a swarm but could be modified to do so.
- [Giant LED Disco Ball](https://blog.hackster.io/get-the-party-started-with-this-giant-led-disco-ball-cd776451e3c0) This is a well designed project that used custom-printed PCBs to create a geodesic sphere. Each PCB housed a few Neopixels. The design is meant to be mobile and run off of large LiPo batteries.
  - This design differs from the DSB in that the DSB is smaller, lighter, cheaper to fabricate and WiFi enabled. It is not addressable in a swarm but could be modified to do so.
- [Neopixel LED EyeBall](https://www.hackster.io/H0meMadeGarbage/neopixel-led-eyeball-8da098)
  - This is just a few Neopixels taped to a half-sphere meant to be carried around. Not exactly a comparison but it does come up when you search google for "LED Sphere".
- Hackster.io and Youtube.com have some DIY POV-type cylindrical and spherical displays such as [this](https://www.hackster.io/hanoba_DIY/pov-cylinder-with-arduino-due-7016d5), [this](https://www.hackster.io/wslaton/easy-pov-display-9f4a88), [this](https://www.youtube.com/watch?v=sEY6N4HkSDM), [this](https://www.youtube.com/watch?v=-1Qe17flj0U), or [this](https://www.youtube.com/watch?v=Pf4IyXFTvT4). [This design](https://www.youtube.com/watch?v=_hprsvsPpEI) was a interesting take on the POV display but POV would not be reliable in the same environment as the DSB.
  - POV displays would not be practical to hang in a tree due to the moving parts and exposed electronics. Any slip joint would be prone to water infiltration.
- Youtube.com has some commercial displays that are similar such as [this](https://www.youtube.com/watch?v=te4uvfAzgXY), [this](https://www.youtube.com/watch?v=v2Eh44Rp4_Q), [this](https://www.youtube.com/watch?v=sEY6N4HkSDM), or [this](https://www.youtube.com/watch?v=mB8hct78ETk).
  - All these projects look terribly expensive and out of reach for the DIY community.

## Sequences/Modes/Animations
Read the [Communication Structure](/CommunicationStructure.md) document for a better understanding of Sequences, Commands, Command Elements, and Parameters.

The following section documents the animations available on the DSB. A mode and animation are virtualy synonomous. However, a mode can specify some non-animation commands such as "standby".

Animations are pre-built for the light strip. Each animation is governed by the list of parameters sent in the mode command. See this reference for a list of the parameter types. An animation can be as simple as turning on/off a single pixel. But an animation can be complex such as a pulse (fade from a start color to an end color and then back to the start color).

The "M" mode command can trigger the following animations:

0. Standby
   - Runs the All Off animation once then waits for incomming commands. ~~If a duration is specified, the Photon will sleep for the specified duration.~~ (consider puttin sleep on roadmap).
1. All Off
   - Turns all LEDS repeatedly.
2. Object On
   - Turns on objects specified in the object array. 
   - Defaults to "All" if no object array specified. Defaults to black (off) if no color array specified.
   - Optional Parameters: A, C, O, 

11. Fade
    - Fades from one color to the next. 
    - The colors change slightly between the start and end color on each step advance. The amount of change is based on the number of steps (T) specified and the start and end colors. 
    - If repeat (R) is specified, on each repeat, the next 2 color in the color array will be used. If there are more repeats than colors, the color array index will wrap around.
      - For example, using this color array `"C":[0,255,65280,16711680]`
        1. On the first run the fade will go from 0 (black/off) to 255 (blue). 
        2. On the first repeat (2nd run), the fade will go from 255 (blue) to 65280 (green). 
        3. On the 2nd repeat (3rd run) the fade will go from 65280 (green) to 16711680 (red). 
        4. If there is a 3rd repeat (4th run) the start color will be 16711680 (red) and the end color will wrap around to the first color in the color array which is 0 (black/off). 
        5. If there is a 4th repeat (5th run), the fade will operate exactly as the first run.
    - Alternate/Sub Modes
      - Pulse - Fades up then fades down. Using this example `"M":11,"U":5000,"T":100,"R":1,"A":1,"C":[0,255,0]`, on the first run, the animation will start at color 0 (black/off) and ramp up to color 255 (blue) over 5 seconds and 100 steps (which is a pretty smooth transition). On the 2nd run, the animation will fade back to 0 (black off) over the same number of steps.
      - Pulse with high/low hold - Fades to a color, stays on that color before fading to the next color. Using this example `"M":11,"U":5000,"T":100,"R":2,"A":1,"C":[0,255,255,0]`, on the first run, the animation will start at color 0 (black/off) and ramp up to color 255 (blue) over 5 seconds and 100 steps (which is a pretty smooth transition). On the 2nd run, the animation will stay at color 255 (blue) for 5 seconds. On the 3rd run, the animation will fade back to 0 (black off) over the same number of steps.
    - Required Parameters: C
    - Optional Parameters: O, R

12. Fill
    - Fills the ball with a specified color.
    - The object array specifies the starting point for the fill operation. Multiple objects (even of differing types) can be specified.       - For example, using this object array `"O":["C0","C11","R0"]`, on the first step, columns 0 and 11 and row 0 will turn on. On the 2nd step, columns 1 and 12 and row 1 will turn on. On the 3rd step, columns 3 and 13 and row 3 will turn on. Etc.
    - Alternate/Sub Modes
      - Vertical Spin - The width parameter specifies the number of objects to keep on. Using this example `"O":["C0"],"I":0,"H":5`, the animation will keep 5 columns lit starting with column 0 and will spin in the clockwise direction.
      - Twinkle - Twinkle is a random lighting of pixels. On each subsequent step, a number of pixels are exchanged (some turned off, some turned on). Use "I":254 (randomized direction) and "H":xxx (number of objects on) in conjunction for a twinkle effect. You can twinkle by column, row or pixel.
    - Required Parameters: O, C
    - Optional Parameters: A, I, H
    
13. Spin
    - Spins either vertically or horizontally. A "spin" is a sequential lighting of objects in a particular direction. The Vertical spin is just a wrapper around the fill mode with a width. Spinning a single pixel (or group of pixels) or spinning horizontally (row spin) requires a custom routine.
    
14. Flash
    - Flash starts with a solid color and then shows another color at full brightness for a very brief amount of time before returning to the original color.
    
## Particle Photon Demonstration
Makers who do not want to build the DSB may still benefit from some of the demonstrated methods on the Particle Photon platform including:
- parsing JSON strings on the IoT hardware,
- receiving and parsing variables sent via JSON where the JSON payload contains a varying number of variables,
- using a single Particle cloud subscription to address multiple devices, filtering commands by a target address,
- using the built in Log functionality, sending logs to an external service such as papertrailapp.com,
- using classes for object-oriented programming on IoT devices,
- using both UDP and particle cloud functions to receive commands.
    
## Design Walkthrough  
My first CAD iterations used a solid spherical shell with LEDS in horizontal rows. In order to make animations easy to design in software, I knew it would be best to use the same number of LEDs in each row/column. Once I saw the first design in TinkerCad, I knew I would have problems laying the flat ribbons horizontally as they would not conform to the sphere well. When horizontal, each strip would be a different length and my sphere might start to look like a stepped cylinder rather than a sphere. Then I started to lay them out in a vertical orientation. This was a much better design as the strips could all be uniform in length. Since the max dimension of the 3D printer is 250mm, that was my starting sphere radius. I chose to include 24 verticals to have a fairly dense pixel spacing. All in, that would be 23 pixels * 24 strips = 552 pixels. 
  
Because of the strip width (14mm), each vertical couldn't converge directly in the center of the north/south poles. I would have to space the vertical strips so that they converged on top and bottom support rings and design a fastening system. The strips looked nice when I layed them out around a 100mm diameter ring. I decided to fasten all these 3D printed vertical "arms" to the rings using stainless steel screws. So now I have a rough shell that looks a bit like a torroid rather than a sphere... but it's not that noticable (unless you ask my wife which calls it the "LED pumpkin.")
  
I looked for a power source that could handle the 552 LEDs and fit within a 250mm sphere. At this point, I already ordered the LED strips from AliExpress. They are based on the SK9822 chipset (which is apparently a better knock-off of the APA102 chip). I had a few 1 meter prototyping strips from Adafruit but I needed approximately 10 meters for this project. Using AliExpress lowered the cost to approximately $10/meter as opposed to using Adafruit at approximately $40/meter. The LEDs represent the single biggest cost in the bill of materials. To calculate the total power usage using the (not very clear) datasheet, I used a worst-case value of 20ma/color/pixel * 3 colors (RGB) * 552 pixels = 33.12 amps total current at 5 volts. Of course you should always oversize a PS so you run at about 80% of maximum capacity to account for spikes. The outdoor power supplies (PS) on Amazon looked expensive and didn't fit my desired footprint. I chose a ~$17 40A, 5V internal PS from Amazon. Going by the specified PS dimensions, I could now design a housing for it. The design was a bit tricky and I printed several partial designs on the 3D printer to make sure it would print right. To shorten a very long story, I ended up using a multi-part/modular cylinder design printed in PETG to act as the internal support structure. The PS would be encased in this cylinder and not accessible after the DSB is assembled. I included an side-opening and rain shield to accomodate a 30mm fan for ventilation. I anticipate incorporating a temperature sensor within the PS housing which activates the fan when needed.

After cutting the LED reels into 23-pixel columns, I soldered them all together with hook-up wire incorporating 6 power taps (one tap every 4 columns.) The strips are wired in a daisy chain where the dataflow is "up" on the first strip and then "down" on the second strip and alternates in that manner for the entire length of the chain. To attach the strips to the support structure, I anticipated simply using zip ties (they are low-cost, expendable, and they work). However, the zip tie crushed the silicone jacket excessively and I anticipated issues with the silicone breaking or leaking over time. So I went back to the 3D printer and created hundreds of clips using crystal clear PETG (to be light transparent). The clips held the silicone snugly to the support structure. The larger of the 2 clips I designed had detents so that you could put a zip tie around both the support structure and clip for a more snug fit without crushing the silicone jacket.

## Assembly
1. Start by assembling the power supply. Install the main power feed and the LED strip power connections. You may want to run a functions check prior to encasing the power supply in the support structure; hookup the power supply, LED strip and electronics and run through some animations.
2. Assemble the 3D printed objects. See the [readme](/DotStarBall/stl/README.md) in the stl folder for a detailed write up on just the 3D printed components.
3. Solder the LED strip together.
4. Affix the LED strip to the support structure using clips. Start with the first strip and work your way around the ball.
5. Connect the LED strip power connections to the power supply.
6. Assemble the electronics PCB to the electronics housing.
7. Connect the electronics PCB to the LED strip 4-pin JST connector.
8. Affix the electronics housing to the underside of the support structure. Take care to ensure all power cables are tucked up into the ball and do not put excess force on any electronic components.
9. Affix the hanging bracket to the top of the ball.

## Installation In a Lighting Display
Note: For complex animations, the DSB will most likely be driven by a controller using UDP networking. Because UDP does not guarantee delivery of packets (it's more of a "best effort" service), you must ensure the DSB is connected to a reliable and "quiet" network (minimal UDP/multicast/broadcast traffic). To ensure the best reliability, provid a dedicated WiFi access point or router and place all DotStar swarm components in a private VLAN. In order for DSB components to communicate with each other, they must all be on the same network subnet. In order to use Particle Cloud communication, all DSB components must also be able to contact the internet.

1. Install the assembled ball in your lighting display. (Depending on the setup, this may include associating the Particle Photon to a new WiFi network. You should complete the WiFi association before installing the ball in its final location.)

