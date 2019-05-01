// Fall 2018

#pragma once

#include <glm/glm.hpp>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"

void A4_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters
		 glm::vec3 & ambient,
		 std::list<Light *> & lights
);
struct RenderObject{
	static SceneNode * root;
	static Image * image;

	static int w, h;
	static glm::vec3 * orig;
	static double fov;
	static double aspect;
	static glm::mat4 *inverseV;

	static  glm::vec3 * ambient;
	static  std::list<Light *> * lights;

	RenderObject();

	void renderPixel(uint x, uint y);

	static void setValueStaticMembers(SceneNode * root,

			// Image to write to, set to a given width and height
									  Image  * image,

									  int w,
									  int h,
// Viewing parameters
									  glm::vec3 * orig,
									  double fov,
									  double aspect,
									  glm::mat4 *inverseV,

			// Lighting parameters
									   glm::vec3 * ambient,
									   std::list<Light *> * lights
									  );
};



class Ray{
public:
	glm::vec3 o, d;

	Ray(glm::vec3 a, glm::vec3 b): o(a), d(b) {};

	glm::vec3 computePoint(double t);
};