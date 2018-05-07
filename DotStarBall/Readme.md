# DotStar Ball (aka. DotStar Sphere)
The first object designed was the DotStar Sphere. When I started designing this object, I used the some of these criteria:
- had to be large enough to have a visual impact haning on a large tree branch,
- had to be (relatively) low cost since I had to make many of them,
- has to receive commands external commands and display animations from that input.

  #### Constraints
  - Anything I create has to live outdoors. So it has to be designed to handle Northeastern US weather (snow, rain, high-winds, etc.)
  - I knew I would be using DotStar LED strips. I used them for a previous project and found them easy to use and program. These strips optionally come with a silicone jacket with an IP67 rating which satisfies the weather issue. To keeps costs low and with a rough guestimate of the size of the sphere, I chose the version with 60 pixels/meter which would give me a pixel spacing of 16.67mm.
  - I have a 3D printer so I knew that I would most-likely design and print a custom support structure to keep it light and low cost. I have an original Prusa i3 Mk2 printer with maximum print dimensions 250x200x180mm.
  
  #### Design Walkthrough  
  My first iterations used a solid spherical shell with LEDS in horizontal rows. In order to make animations easy to design in software, I knew it would be best to use the same number of LEDs in each row. Once I saw the first design in TinkerCad, I knew I would have problems laying the flat ribbons horizontally as they would not conform to the sphere well. When horizontal, each strip would be a different length and my sphere might start to look like a stepped cylinder rather than a sphere. Then I started to lay them out in a vertical orientation. This was a much better design as the strips could all be uniform in length. Since the max dimension of the 3D printer is 250mm, that was my starting sphere radius. I chose to include 24 verticals to have more dense pixel spacing. All in, that would be 23 pixels * 24 strips = 552 pixels. 
  
  Because of the strip width (14mm), each vertical couldn't converge directly in the center of the north/south poles. I would have to space the vertical strips so that they converged on top and bottom support rings and design a fastening system. The strips looked nice when I layed them out around a 100mm diameter ring. I decided to fasten all these 3D printed vertical "arms" to the rings using stainless steel screws. So now I have a rough shell that looks a bit like a torroid rather than a sphere... but it's not that noticable (unless you ask my wife which calls it the "LED pumpkin.")
  
  I looked for a power source that could handle the 552 LEDs and fit within a 250mm sphere. At this point, I already ordered the LED strips from AliExpress. They are based on the SK9822 chipset (which is apparently a better knock-off of the APA102 chip). I used AliExpress because of the 
