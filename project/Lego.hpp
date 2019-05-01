#pragma once

#include "Primitive.hpp"
#include "SceneNode.hpp"
#include "Material.hpp"


class Lego :public Primitive{
	int w;
	int l;
	bool flat;
	SceneNode* brick= nullptr;
	void construct();

public:
	Lego(int,int,bool);

	Lego(const Lego &o);

	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;

	virtual ~Lego();

};


