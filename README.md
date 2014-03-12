***Skyline*** (2014) by Tobias Zehntner
=======

Code for Skyline (2014): LED strip controlled through Arduino and indirectly openFrameworks

This is the code for my work Skyline (2014). An LED strip controlled by Arduino, with values calculated by openFrameworks. The Arduino cycles through keyframes, putting out the color to the LED strip by fading between keyframes. Check my [website](http://www.tobiaszehntner.com) for details.

##openFrameworks

The code for openFrameworks reads out the RGB values of each pixel from a keyframe (vertically), and writes it as output, including information on how many pixels and how many keyframes there are. Copy/paste the readout to Arduino. Place keyframes named as <####.jpg> in the `bin` folder of your openFrameworks app directory.

##Arduino
The code in the Arduino file takes the RGB values of the keyframes, calculates the color between them as time passes, and sends them to each RGB LED pixel on the strip.