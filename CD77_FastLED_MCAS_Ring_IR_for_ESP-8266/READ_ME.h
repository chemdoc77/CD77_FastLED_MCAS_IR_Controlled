/*
                                         Read Me
                                  CD77_FastLED_MCAS_RING

Now you can jump from one sketch to another sketch as easy as it is to change stations on your TV.
How?  Use Chemdoc77’s multiple complex animations sketch method (MCAS) to create a sketch which contains many other sketches.  
This sketch uses Chemdoc77’s MCAS method to contains multiple complex animations in one sketch.  

Now one can have many different sketches in one sketch.  You can jump from seeing one sketch to seeing another sketch at any 
time by using an IR controller.  This is made possible by the ability to have multiple instances of a modified version 
of Mark Kriegsman’s Time Code Performance sketch in a single sketch.  Mark Kriegsman’s Time Code Performance sketch as found in:

https://gist.github.com/kriegsman/a916be18d32ec675fea8

This is also made possible by using Sam Guyer’s fork of FastLED for ESP32 MCUs as found in:

https://github.com/samguyer/FastLED


                          ======   Important NOTES   ======

You may have to predeclare functions when a function is causing problems if you get error message 
for that function when compiling the MCAS sketch.

When combining sketches in MCAS, you need to rename common variables used in more than one of the sketches 
being combined. If hue is used in two sketches then it must be renamed as example to huedr100 for 
use in the DemoReel100 sketch used in the MCAS sketch.

There are still a few tiny bugs in the sketch.  You may have to press a button on the IR controller more than one time to change sketches.

You have to remove parts of the initial lines of a imported sketch being put into the CMAS sketch. You have 
to remove the setup and loop parts from the imported sketch that is to be included in the CMAS sketch.  
However, variables and other important information must be copied from these sections of the imported sketch into the CMAS sketch.
This can be seen if one examines the DemoReel100.h tab in this sketch and the original DemoReel100 sketch as seen in:

https://github.com/samguyer/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino








 */
