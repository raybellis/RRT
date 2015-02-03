# RRT - Ray's Ray Tracer

RRT is a _stochastic_, _multithreaded_ ray tracer written in C++ that relies on casting a very high number of samples per pixel into the scene and then scatters diffuse rays in every direction.

The method is far from efficient and producing a noise-free image may take thousands of samples per pixel (and hours of CPU time) but it produces effects "for free" that many other ray tracers can only approximate, including:
- diffuse inter-reflection (colour bleeding)
- area lighting and soft shadow
- glossy surfaces
- depth-of-field
- caustics

The current implementation supports only a limited number of 3D primitives:
- spheres (of course!)
- cubes
- infinite planes
- compound (parent node for collections of the above)

Arbitrary homogenous transformations are supported to move and deform primitives, but as yet these transformations cannot be nested.  That is to say, a compound node cannot yet have a transformation that applies to all child nodes within it.

There is no scene description language - the user has to write a C++ program that makes call to the RRT APIs that create nodes, attach shaders to nodes, etc.

The most powerful shader is `Shader::stochastic` that can take a `surface` object that is similar to those used in other ray tracers and will automatically cast a single diffuse ray, a specular reflected ray and a tranmitted ray, depending on the surface's properties.

For a surface that has purely diffuse lighting properties the `Shader::diffuse` shader can be used instead and is slightly more efficient than `Shader::stochastic` because it doesn't have to consider the surface properties to decide whether to cast any non-diffuse rays.

There are no "lights" in RRT.  Any object can have a `Shader::constant` shader attached to it that makes that object a fixed colour and indirectly causes it to "illuminate" any object that casts a ray in its direction.

## Compiling

RRT requires a C++11 compatible compiler, Boost, GD, libpng, libjpeg and libz.  The supplied Makefile is for Mac OS X with macports.

Two samples scenes are included so far, "snooker" and "cornell".

## TODO
- More primitives (especially meshes!)
- Bounding volume / Spatial acceleration techniques
- Compound transformations
- Time-based transformations (motion blur!)
