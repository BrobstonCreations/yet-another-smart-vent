## Vent Printing

- I would recommend printing the louvers with 100% infill. I've printed everything else with 23% infill or less.
- On my Prusa I put down a layer of glue stick everywhere that I will be printing, this does a pretty good job for bed adhesion. On my RatRig with the Filament PEI sheet, I haven't needed any gluestick for ABS.
- With the thin long layers on the electronics enclosure and lid I've added "brim ears" when slicing (with SuperSlicer) and this has resolved warping/curling with ABS.

Here is the correct orientation to print things. Nothing in this picture requires supports, as long as bridging works fine on the inside of the female end of the louvers. What is not pictured includes: four levers (for 4x10) and the vent top.
![4x10-on-build-plate](https://user-images.githubusercontent.com/4724577/184463112-e18aceac-d279-469a-ad77-89d0d91e50bf.jpg)

### Semi-print-in-place lever/linkage assembly

The next time I print the levers I will add more pictures, in general the process goes like this:
1. Open the STL file for the four levers (if 4x10 vent) in your slicer.
2. Face the flat side down.
3. Add supports for the servo wiper arm relief.
4. Add a pause to the print right after the cylinder that the linkage rides on finishes printing.
5. Export the gcode to the printer and begin printing.
6. During the pause, place the linkage on top of the printed cylinders; be sure that the linkage aligns at least somewhat well with the cylinders; if it doesn't, some bending of the linkage may be needed... then resume the print. 
7. Once the print is finished, be sure to press down on the linkage on either side of the cap that was added to each lever; you will hear an audible snap/pop, this is the linkage being released from the lever. Repeat for all the levers. See pictures below:
![PXL_20220812_203345301](https://user-images.githubusercontent.com/4724577/184463430-79111150-4b26-4e60-8fb8-e5c4ca5b48d1.jpg)
![PXL_20220812_203557913](https://user-images.githubusercontent.com/4724577/184463431-fc98c2f6-2acf-437e-8567-8cfb148f5f4b.jpg)
8. At this point each lever should spin freely on the linkage.

### Vent Top
- The vent top should be printed upside down.
- Supports are needed for any overhangs that are parallel with the print bed, like the overhangs that the bottom of the M5 screw head presses against when installed.
