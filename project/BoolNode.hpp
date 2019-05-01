//
// Created by dtchorni on 24/11/18.
//

#pragma once

#include <vector>
#include "SceneNode.hpp"
#include <vector>

enum class BoolType{
	Intersect,
	Union,
	Difference
};

class BoolNode : public SceneNode {
	BoolType booltype;

public:
	BoolNode(const std::string & name, int type);

	virtual Intersection * trace(glm::vec3 p, glm::vec3 u) override;

	Intersection * _union(std::vector<Intersection*>&, glm::vec3 p, glm::vec3 u);
	Intersection * _intersect(std::vector<Intersection*>&, glm::vec3 p, glm::vec3 u);
	Intersection * _difference(std::vector<Intersection*>&, glm::vec3 p, glm::vec3 u);

};


