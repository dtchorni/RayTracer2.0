// Fall 2018

#pragma once

#include "SceneNode.hpp"
#include "Primitive.hpp"
#include "Material.hpp"
#include "Light.hpp"

class GeometryNode : public SceneNode {
public:
	GeometryNode( const std::string & name, Primitive *prim, 
		Material *mat = nullptr );

	void setMaterial( Material *material );

	glm::vec3 calculateCol(Intersection intersection,const std::list<Light*> sources, SceneNode *root, glm::vec3, glm::vec3, glm::vec3 ambient);

	Intersection * trace(glm::vec3 p, glm::vec3 u) override;



	Material *m_material;
	Primitive *m_primitive;
};
