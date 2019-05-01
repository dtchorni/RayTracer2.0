# CS488 Final Project

### By: Daniel Tchorni

A raytracer was chosen to for the final project.

## Compilation:

Ditching premake4, I have decide to use CMake instead. Simply make a directory  (ex: `mkdir cmake-release`), enter that directory and run `cmake ..`. For a huge performance boost add the `cmake -DCMAKE_BUILD_TYPE=Release ..` and exit that directory.

## Usage:
This raytracer comes loaded with a few features, all which can be modified with flags. Running requires you pass in a Lua file as your first input (ex: `./raytracer Assets/scene.lua`). Pass the `-h` for more verbose options and descriptions. An example output with this flag is shown below:

```
Ray Tracer: by Daniel Tchorni
Usage:
	 [*.lua file]
		 -d (exclude diffuse portion of lighting calculation
		 -s (exclude specular portion of lighting calculation
		 -a (exclude ambient light calculation) 
		 -b (produce the bounding volumes rather than the meshes
		 -sh (remove shadows)
		 -ph (Completely disable Phong lighting)
		 -th (disable multi-threading optimizations)
		 -nth [n] (run with n multiple threads) 
		 -go (disable Gourard shading) 
		 -ua (default all boolean nodes to union operations) 
		 -db (debug mode -> disables multi-threading and anti-aliasing)
		 -ss [n] (enter number of points per pixel to sample with) 
		 -h (Print dialogue)
```

## Objectives:
	1. New primitives: cone, cylinder
	2. Furniture models
	3. Constructive Solid Geometry
	4. Modelling using CSG
	5. Procedurally generated Lego structures
	6. Refraction
	7. Rendered scene
	8. Photon mapping casting
	9. Photon mapping gathering
	10. Stochastic sampling

