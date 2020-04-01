# MiniRT

A ray-tracer, written in c.

This program uses the ray-tracing protocol to generate images. The images represent scenes which are defined by simple geometric objects, a lighting system and one or more cameras with specified angle and position.

## Details

The ray-tracing algorithm is implemented in c and (due to the rules of the project) the only external functions used are those in the math.h library, along with and a handful of other basics (such as malloc and free).

The pixel rendering, window management and event handling aspects are dealt with using functions from the miniLibX, a simple X-Window (X11R6) programming API in C, designed for students and written by Oliver Crouzet. This in turn makes use of the AppKit and OpenGL frameworks.

The program takes as it's first argument a scene description file with the ```.rt``` extension which specifies the image details. It contains information for the:

* image resolution
* ambient lighting (brightness and colour)
* spot lighting (position, brightness and colour of spots)
* cameras (position, angle and field of view)
* objects (position, dimension, colour and orientation where applicable)

The objects that can be generated are:

* sphere
* plane
* square
* triangle
* cylinder

Here is an example of such an ```.rt``` file:

![.rt](scene.rt)

## Some examples of generated scenes

![](sphere.png)
A simple sphere illuminated by two spot lights.


![](planet.png)
The same sphere, this time with another nearby, and a single spot.


![](cylinder.png)
A cylinder, viewed from one end.


![](sphere-cylinder-plane.png)
A horizontal plane, a sphere and a cylinder. Two spots, one above and one inside the cylinder.

## License

MinilibX is licensed under the BSD license: Copyright Olivier Crouzet - 1999-2015.
