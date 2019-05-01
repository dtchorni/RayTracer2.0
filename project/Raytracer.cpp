// Fall 2018

#include <glm/ext.hpp>
#include "Options.hpp"
#include "Raytracer.hpp"
#include "GeometryNode.hpp"
#include "PhongMaterial.hpp"
#include <cs488-framework/MathUtils.hpp>
#include <iomanip>
#include <queue>
#include <stdlib.h>

glm::vec3 Ray::computePoint(double t) {
	return o + ((d)*t);
}


SceneNode * RenderObject::root=nullptr;
Image * RenderObject::image=nullptr;

int RenderObject::w=0;
int RenderObject::h=0;
glm::vec3 * RenderObject::orig=nullptr;
double RenderObject::fov=0;
double RenderObject::aspect=0;
glm::mat4 *RenderObject::inverseV=nullptr;

glm::vec3 * RenderObject::ambient=nullptr;
std::list<Light *> * RenderObject::lights=nullptr;

RenderObject::RenderObject() {}

void RenderObject::setValueStaticMembers(SceneNode *r, Image *i, int q, int e, glm::vec3 *o, double f,
										 double as, glm::mat4 *inv,  glm::vec3 *amb,
										  std::list<Light *> *li) {
	root=r;
	image=i;
	w=q;
	h=e;
	orig=o;
	fov=f;
	aspect=as;
	inverseV=inv;
	ambient=amb;
	lights=li;
}

void RenderObject::renderPixel(uint x, uint y){
	glm::vec3 totalColor(0);
	for(int s=0; s<options.samples; ++s) {
		double pCAMx;
		double pCAMy;

		/*if(x==220&&y==267){
            std::cout<<"hi"<<std::endl;
		}*/

		if (options.samples == 1) {
			pCAMx = ((2 * ((x + 0.5) / w)) - 1) * aspect * fov;
			pCAMy = (1 - (2 * ((y + 0.5) / h))) * fov;
		} else {
			double randX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			double randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			pCAMx = ((2 * ((x + randX) / w)) - 1) * aspect * fov;
			pCAMy = (1 - (2 * ((y + randY) / h))) * fov;
		}

		glm::vec3 dir = glm::vec3(pCAMx, pCAMy, -1);

		dir = glm::vec3(*inverseV * glm::vec4(dir, 0));

		dir = glm::normalize(dir);


		Intersection *inter = root->trace(*orig, dir);
		if (inter != nullptr) {

			glm::vec3 col = inter->obj->calculateCol(*inter, *lights, root, *orig, dir, *ambient);

			totalColor+=col;

			/*(*image)(x, y, 0) = col.r;
			(*image)(x, y, 1) = col.g;
			(*image)(x, y, 2) = col.b;*/


		} else {
			/*(*image)(x, y, 0) = 1.0f - ((float) y / (float) h);
			(*image)(x, y, 1) = 1.0f - ((float) y / (float) h / 2.0);
			(*image)(x, y, 2) = 1.0f - ((float) y / (float) h) / 4.0;*/
			glm::vec3 background(
					(float)(1.0f - ((float) y / (float) h)),
					(float)(1.0f - ((float) y / (float) h / 2.0)),
					(float) (1.0f - ((float) y / (float) h) / 4.0)
					);
			totalColor+=background;
		}
	}
	totalColor=totalColor/options.samples;
	(*image)(x, y, 0) = totalColor.r;
	(*image)(x, y, 1) = totalColor.g;
	(*image)(x, y, 2) = totalColor.b;
}


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
) {

// Fill in raytracing code here...  

std::cout << "Calling A4_Render(\n" <<
	  "\t" << *root <<
	  "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
	  "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
	  "\t" << "view: " << glm::to_string(view) << std::endl <<
	  "\t" << "up:   " << glm::to_string(up) << std::endl <<
	  "\t" << "fovy: " << fovy << std::endl <<
	  "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
	  "\t" << "lights{" << std::endl;

for(const Light * light : lights) {
	std::cout << "\t\t" <<  *light << std::endl;
}
std::cout << "\t}" << std::endl;
std:: cout <<")" << std::endl;

size_t h = image.height();
size_t w = image.width();

double aspect = w/h;

double fov = tan(degreesToRadians(fovy)/2);

RenderObject * render = new RenderObject();



glm::vec3 orig = eye;

glm::mat4 V = glm::lookAt(eye,view,up);
glm::mat4 inverseV = glm::inverse(V);

//	orig = glm::vec3(inverseV*glm::vec4(orig,1));

//    std::cout<<orig<<endl;

RenderObject::setValueStaticMembers(root, &image, w, h, &orig, fov, aspect, &inverseV, &ambient, &lights);

int loop=0;
int total = h*w;
//	options.cores=total;
std::queue<int> thread_order;

if(options.thread) {
	options.pool = std::vector<std::thread *>(options.cores, nullptr);//.reserve(options.cores);
	for(int i=0; i<options.cores; ++i){
		thread_order.push(i);
	}
}
for (uint y = 0; y < h; ++y) {
	for (uint x = 0; x < w; ++x) {
		if(options.thread){
			int ind;


			ind = thread_order.front();
			if(options.pool[ind]!=nullptr) options.pool[ind]->join();
			delete options.pool[ind];
			thread_order.pop();



			options.pool[ind]= new std::thread(&RenderObject::renderPixel,render, x, y);
			thread_order.push(ind);

		}else {
			render->renderPixel(x, y);
		}

		loop++;

		if(loop%5==0) std::cout<<"\r"<<(int)((float)(100*loop)/(float)total);

	}
}
std::cout<<std::endl;
if(options.thread) {
	for (int i = 0; i < options.pool.size(); ++i) {
		if (options.pool[i]->joinable()) {
			options.pool[i]->join();
			delete options.pool[i];
		}
	}
}
delete render;

}
