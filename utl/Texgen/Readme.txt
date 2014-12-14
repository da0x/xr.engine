Terrain Texture Generator
(c) 2001 Insane Software

Here's a little toy that synthesizes a unique terrain texture
by blending a set of base texture layers (according to their
parameters). Given a light direction, it can also calculate
per pixel lighting. 

Ok first I'll explain the texture layer parameters:

Each layer consists of an image, and a set of parameters that
tell the programm how and where to blend this image into the
target texture. With the altitude constraints you can limit
this layer to appear only between "Min" and "Max" (0.0 beeing
the lowest possible level and 1.0 beeing the highest possible
level). The "Min Value" and "Max Value" define the alpha value
at the "Min" and "Max" levels.
With the slope constraints you can further limit this layer to
a certain "steepnes" of the terrain. This layer only appears
if the slope at the current heightmap pixel is between the
"Min" and "Max" parameters (0.0 beeing absolut flat and 90.0
beeing totally vertical. Actually this is the angle between
the heightmap normal and the up-vector (0,1,0) in degrees).
Again the "Min Value" and "Max Value" are the alpha values
at the "Min" and "Max" slopes. That's it!

I guess the options tab needs a bit explaining too:

The "texture size" combobox determines the size of the output
texture. The "slope threshold" is a value used during slope
calculation. It's something like a tolerance value. If the
slider is all the way left, every little variation of the
heightmap luminance produces a different slope, if the slider
is all the way right only big changes of heightmap luminance
produce a noticeable slope.
If the "lighting" checkbox is checked, the generator does
perpixel lighting calculations. Enter the light direction
vector below "light direction" (xyz order).
Use the "light influence" slider to change the contrast
of the output texture. It basicaly determines "how much"
light is applied. If the slider is all the way left, the
lighting has almost no effect on the output texture.

I have included a couple of example script that you can load.
If you play a bit with the parameters you can produce very
realistic landscape textures (the included are not that
realistic, mainly because of the textures...). You can even
use it to add perpixel lighting to your existing textures only
(see the "AddLighting" example"). 

Some things to note:

-Textures/Heightmaps need not be square
-To create a high res texture you need a high res heightmap.
 If you create a 512x512 texture from a 32x32 heightmap it will
 be awfully "blocky". I tried to reduce this effect by adding
 subpixel accuracy and interpolating altitude/slope between the
 pixels, but it didn't help much
-In the "Texture" tab you can find a "Preview" button. You need
 nebula (www.radonlabs.de) and the optional nflatterrain package.
 When pressed the first time it will ask you to locate the
 gfxserv.exe file (it's usually in the nebula/bin/win32 directory).

If you have further questions look at our website 
(http://insanesoftware.exit.de) and/or ask me!

Happy texturing,
Dirk
ulbdir@web.de
