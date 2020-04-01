# MiniRT

A ray-tracer, written in c.

This program uses the ray-tracing protocol to generate images. The images represent scenes which are defined by simple geometric objects, a lighting system and one or more cameras with specified angle and position.

## Details

Talk about what I wrote.

The actual rendering and event handling aspects are dealt with using the miniLibX, a simple X-Window (X11R6) programming API in C, designed for students and written by Oliver Crouzet. This in turn makes use of the AppKit and OpenGL frameworks.

The program takes as it's first argument a scene description file with the ```.rt``` extension which specifies the image details. It contains information for the:
                                            * image resolution
                                            * ambient lighting (brightness and colour)
                                            * spot lighting (position, brightness and colour of spots)
                                            * cameras (position, angle and field of view)
                                            * objects (position, dimension, colour and orientation where applicable)
                                            
## License

MinilibX is licensed under the BSD license: Copyright Olivier Crouzet - 1999-2015.
