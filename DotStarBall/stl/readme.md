# 3D Printed Objects for the DotStar Ball (DSB)
All components were designed in [TinkerCad](https://www.tinkercad.com/#/) and printed on a [Prusa i3 Mk2](https://www.prusa3d.com/). Filament used was [MakerGeeks PETG](https://www.makergeeks.com/collections/maker-series-petg) at 255°C with a heated bed at 80°C. All .STL files were sliced on [Sli3er Prusa Edition](https://www.prusa3d.com/slic3r-prusa-edition/) 1.39.1 or better.

## Components
1. **PSU Cylinder** (5 components)
   - This is the internal support structure for the DSB. The cylinder has an internal rectangular slot which accepts a 5V, 40A power supply. The cylinder is modular with 3 parts (top, mid, bottom). The parts are overlapping for an [IP 42 rating](https://en.wikipedia.org/wiki/IP_Code) (does not allow downward falling rain or snow within the enclosure.) 
   - **Top Cylinder**
     - Has 24 mounting holes for attaching LED arms with [#6-1/2" stainless steel self-tapping screws](https://www.fastenermart.com/SC165-1452.html).
     - Recommended Print settings: .2mm layers, 5 solid layers top and bottom, 3 perimeters, 25% infill or more, supports off. Must be printed with the smaller diameter end touching the build plate.
   - **Mid Cylinder**
     - Has mounting holes for a 30mm case fan. When installing a fan, you should install a small mesh screen between the fan and cylinder to give it the IP 42 rating. If a mesh screen is omitted, bugs and other particulates may infiltrate the cylinder. 
     - Recommended Print settings: .2mm layers, 5 solid layers top and bottom, 3 perimeters, 25% infill or more, supports off. Must be printed with the smaller diameter end touching the build plate.
   - **Bottom Cylinder**
     - Has 24 mounting holes for attaching LED arms (same as top cylinder). Also has a large hole for power cable access. Although you may be able to touch the PSU from this access hole, you should install the power cables to the PSU before encasing the PSU in the cylinder.
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
    
