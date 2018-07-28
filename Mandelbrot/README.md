# Mandelbrot Explorer

## How To Install:
* First download the jar file and be sure to download the config file in the SAME directory as the jar file. I made this for fun so I didnt really feel like adding a ton of logic to deal with where the config file was located, so please put it in the same directory. 
* Also create a rsc directory inside of the directory you download the jar to, so that the images have somewhere to go. 

## How To Use
* Simply edit the config file paramaters then run "java -jar Mandelbrot.jar".
* The config file paramaters are as follows:
 - RESOLUTION: is the width of the resulting image in pixles
 - CENTER: is the complex number that the image will be centered at. (the first number is the real part, the second is the imaginary part). 
 - WIDTH, HEIGHT: Determines the width height ratio.
 - NUM_CYCLES: The number of cycles to determine wether the mandelbrot set converges or not. Increasing this will produce higher quality images, however it will also cost more computation time. 
 - START_COLOR_OUTSIDE: The 255,255,255 starting color of the outside of the set.
 - START_COLOR_OUTSIDE: The 255,255,255 starting color of the outside of the set.
 - COLOR_OUTSIDE: Will determine if the outside of the set is colored according to convergence time.
 - COLOR_INSIDE: Will determine if the INSIDE of the set is colored according to convergence time. (Makes for very cool and unique mandelbrot images)
 - OUTPUT_NAME: Will be the name of the output image + .png. This will also be placed in the rsc folder. 

## Motivation
I created this project mainly because it seemed like a lot of fun. Also I noticed that there could be many more coloring scheemes to the exisiting mandelbrot algorithems, so I wanted to expand on them a little. Enjoy!