# 3D Printed Objects for the DotStar Ball (DSB)
All components were designed in [TinkerCad](https://www.tinkercad.com/#/) and printed on a [Prusa i3 Mk2](https://www.prusa3d.com/). Filament used was [MakerGeeks PETG](https://www.makergeeks.com/collections/maker-series-petg) at 255°C with a heated bed at 80°C. All .STL files were sliced on [Sli3er Prusa Edition](https://www.prusa3d.com/slic3r-prusa-edition/) 1.39.1 or better.

## Components
1. **Power Supply (PSU) Cylinder** (5 components)
   - This is the internal support structure for the DSB. The cylinder has an internal rectangular slot which accepts a 5V, 40A power supply. The cylinder is modular with 3 parts (top, mid, bottom). The parts are overlapping for an [IP 42 rating](https://en.wikipedia.org/wiki/IP_Code) (does not allow downward falling rain or snow within the enclosure.) 
   - The PSU cylinder was designed to be modular for flexibility if creating a larger DSB. For example, I already designed a 500mm diameter ball. To accomodate the larger size, the top and bottom cylinders can be reused an only the mid cylinder needs to be modified, or more easily, add additional mid cylinder pieces to make up the additional length. The mid cylinder for the 250mm DSB is 150mm tall. To accomodate the 500mm DSB, you would need a total of 350mm's of mid cylinder; because it is a modular design, you use two 150mm cylinders and add an additional 50mm cylinder piece.
   - **Top Cylinder**
     - This top-most portion of the PSU cylinder has 24 mounting holes for attaching LED arms with [#6-1/2" stainless steel self-tapping screws](https://www.fastenermart.com/SC165-1452.html). The top cylinder is labeled as 57mm which is the actual length of the piece. There is a 10mm overlap with other pieces which provides the weather-proof design.
     - Recommended Print settings: .2mm layers, 5 solid layers top and bottom, 3 perimeters, 25% infill or more, supports off. Must be printed with the smaller diameter end touching the build plate.
   - **Mid Cylinder**
     - Note: Cylinder pieces are labeled with actual length which is 10mm more than the length contributed to the overall PSU cylinder. There is a 10mm overlap with other pieces which provides the weather-proof design.
     - 160mm w/ fan - This mid-span portion of the PSU cylinder has mounting holes for a 30mm case fan. When installing a fan, you should install a small mesh screen between the fan and cylinder to give it the IP 42 rating. If a mesh screen is omitted, bugs and other particulates may infiltrate the cylinder. 
     - 160mm plain - This mid-span portion of the PSU does not have any holes for fans or other components. It is meant to be a modular portion for creating a larger DSB.
     - 110mm plain - This mid-span portion of the PSU does not have any holes for fans or other components. It is meant to be a modular portion for creating a larger DSB.
     - 60mm plain - This mid-span portion of the PSU does not have any holes for fans or other components. It is meant to be a modular portion for creating a larger DSB.
     - Recommended Print settings: .2mm layers, 5 solid layers top and bottom, 3 perimeters, 25% infill or more, supports off. Must be printed with the smaller diameter end touching the build plate.
   - **Bottom Cylinder**
     - This bottom-most portion of the PSU cylinder has 24 mounting holes for attaching LED arms (same as top cylinder). Also has a large hole for power cable access. Although you may be able to touch the PSU from this access hole, you should install the power cables to the PSU before encasing the PSU in the cylinder.
     - Recommended Print settings: .2mm layers, 5 solid layers top and bottom, 3 perimeters, 25% infill or more, supports off. Must be printed with the smaller diameter end touching the build plate.
   - **Fan Shroud**
     - The fan shround should be mechanically fastened and then sealed to the cylinder to prevent water infiltration. The shroud must be sealed to the cylinder with silicone caulk (removable), epoxy (permanent), or other desired method.
     - Recommended Print settings: .2mm layers, 4 solid layers top and bottom, 2 perimeters, 25% infill or more, supports off. Must be printed with the flat surace (top of shroud) touching the build plate.
   - **PSU Spacer**
     - The internal PSU slot was oversized to house a variety of PSU sizes. As such, it requires a spacer to keep the chosen PSU from moving within the cylinder. You can design a custom spacer for your PSU or use some other method to stop the PSU from moving.
     - Recommended Print settings: .2mm layers, 2 solid layers top and bottom, 2 perimeters, 10% infill or more, supports off.
2. **LED Arm**
   - The LED arm is 3mm thick and has holes on either end for attaching to the PSU cylinder. Version 2 has nubs on the back side designed to keep the LED clips from sliding down the arm. A small amount of material may have to be shaved off of the surfaces where the arms touch each other because of enabling supports.
   - Recommended Print settings: .2mm layers, 4 solid layers top and bottom, 2 perimeters, 25% infill or more, supports on with "Support on Build plate only" enabled. Must be printed so that the curved edge (side of arm) is touching the build plate (it will look like a "C" when viewed from above.)
3. **LED Clips**
   - There are 2 versions of the clip: a 3mm wide version (plain) and a wider 5mm version with indents to keep a 2mm zip tie centered on the clip (zip style).
   
**_Not Ready for Posting_**

4. **Electronics Housing**
   - The electronics are contained in an enclosure bolted to the bottom of the DSB.
   
5. **Hanging Bracket**
   - The DSB is desined to be hung from a branch. The hanging bracket bolts to the top of the unit without any penetrations into the PSU cylinder internal cavity. The bracket may have to be constructed from a sturdier material such as aluminum.
    
## Assembly
Before assembling any 3D printed objects, prepare the power supply by installing the main power feed and the power tap connections for the LED strips.

Note: After printing the top cylinder, inspect the top-most solid surface for water tightness. If the solid surface looks porous, you may want to apply a thin film of epoxy to ensure water tightness. Gorilla Glue 2-part epoxy works well but ensure the epoxy completely dries (24-hours) before installing the LED arms.

1. On the mid cylinder, install a small piece of mesh screen to cover the side-hole and mount the fan directly over the mesh. (The fan is not required but is a good idea for thermal management especially in hotter environments. If you choose not to include a fan, you should still cover the side hole with mesh to keep out insects and dust.) Ensure the mesh does not impede fan movement and route the fan power cable into the cylinder through the side-hole (you may have to poke a small hole in the mesh or trim the mesh to allow the cable to route inside. After the fan is installed securely, install the fan shroud on the outside of the mid cylinder. Apply a small amount of silicone caulk to the mating surface of the shroud and then fasten the shroud to the mid cylinder with #6 1/2" stainless steel screws. _Do not overtighten the screws!_ Ensure the shroud is oriented so that it will shed rain and not collect it when assembled with the other cylider parts.
2. Align the top cylinder with the mid cylinder (there is an indented line running the vertical length of all cylinders that needs to be aligned.) Affix the top cylinder to the mid cylinder with #6 1/2" stainless steel screws. You may want to apply a small amount of caulk where the cylinders touch as well as in the screw holes to prevent water infiltration.
3. Insert the assembled power supply into the bottom cylinder. Route all power cables through the internal cavity and out the bottom access hole. Insert the power supply spacer inbetween the power supply and the cylinder slot (if you do not use the printed spacers, you must pack some material inbetween the cylinder and the power supply to prevent movement. Use material that will not catch on fire when exposed to the elevated temperatures of the power supply.)
4. Align the top/mid cylinder assembly with the bottom cylinder (using the exterior alignment markings). Fasten the top/mid cylinder assembly to the bottom cylinder with #6 1/2" stainless steel screws. You may want to apply a small amount of caulk where the cylinders touch as well as in the screw holes to prevent water infiltration.
5. Affix the arms to the top and bottom cylinders with #6 1/2" stainless steel screws. One method to ensure proper alignment is to install 2 arms directly overtop of the cylinder alignment marks. Next, install 2 arms at 90° from the first 2. Then, work on one quadrant at a time first affixing the top screws for all 5 arms, then turning the ball over and affixing the bottom screws for all five arms; repeat for each quadrant. You may want to apply a small amount of caulk in the top screw holes as added protection from water infiltration.


## Images

### 3D Renders (Tinkercad)

![3D Render - Top View](/DotStarBall/assets/DSB_3DRender_Top.PNG)
![3D Render - Bottom View](/DotStarBall/assets/DSB_3DRender_Bottom.PNG)

### Early Prototypes

![Early Prototype - DSB Cylinder Exterior - in ABS](/DotStarBall/assets/DSB_EarlyPrototype_ABS_Exterior_500px.jpg)
![Early Prototype - DSB Cylinder Interior - in ABS](/DotStarBall/assets/DSB_EarlyPrototype_ABS_Inside_500px.jpg)
