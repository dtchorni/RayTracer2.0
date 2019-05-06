// Fall 2018

#include "PhongMaterial.hpp"
#include "Options.hpp"

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, double shininess )
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
{}

PhongMaterial::~PhongMaterial()
{}

glm::vec3 reflect(const glm::vec3 i, const glm::vec3 n){
	return i-2*glm::dot(i,n)*n;
}

glm::vec3 PhongMaterial::getColour(Intersection inter, std::list<Light *> sources,SceneNode *root,
		glm::vec3 p, glm::vec3 u,glm::vec3 ambient) {
	glm::vec3 diffuse = glm::vec3(0);
	glm::vec3 specular = glm::vec3(0);
	if(options.phong) {
		for (auto light : sources) {
			
			glm::vec3 light_dir = inter.point0 - light->position;
			float dist = glm::length(light_dir);
			light_dir = glm::normalize(light_dir);

//			glm::vec3 light_intensity = 1000.0f * light->colour / (float) (4 * M_PI * dist);

			Intersection *shadow= nullptr;
			if(options.shadows) {
				shadow = root->trace(inter.point0 + (inter.obj_norm0 * 0.0001f) , -light_dir);
			}

			// TODO : fix shadow distance checking with length(v2-v1) < length(w2-w1)

			double light_t = ( light->position.x-inter.point0.x)/(-light_dir.x);
//			double light_t = (inter.point0.x + light->position.x)/(-light_dir.x);
//			light_t = light_t<0 ? -INFINITY : light_t;
//			double shadow_t = shadow ? (inter.point0.x + shadow->point0.x)/((-light_dir).x) : INFINITY;
			double shadow_t = shadow ? ( shadow->point0.x- inter.point0.x)/(-light_dir.x) : INFINITY;

            if(light_t<0 && shadow_t<0){
            	light_t = abs(light_t);
            	shadow_t = abs(shadow_t);
            }else if(light_t>0 && shadow_t<0){
            	light_t=-INFINITY;
            }

			if (options.diffuse&&(shadow == nullptr || /*(shadow_t > dist * 10e-10)||*/ (light_t<shadow_t))) {
				diffuse += (std::max(0.0f, glm::dot(inter.obj_norm0, -light_dir)) * light->colour) /
						   (float) (light->falloff[0] + light->falloff[1] * dist + light->falloff[2] * dist * dist);
			}


			glm::vec3 R = glm::normalize(reflect(light_dir, inter.obj_norm0));

			if (options.spec&&(shadow == nullptr || /*(shadow_t < dist * 10e-10) ||*/ (light_t<shadow_t)))
				specular += float(std::pow(std::max(0.0f, glm::dot(R, -u)), m_shininess));
			if (shadow) delete shadow;

		}
	}

	glm::vec3  col = ((options.ambient ? (ambient*m_kd) : glm::vec3(0)) 
			+ diffuse*m_kd + specular*m_ks);//((float) sources.size());

	if(options.phong) return col;
	else return glm::vec3(m_kd.r,m_kd.g,m_kd.b);
}

