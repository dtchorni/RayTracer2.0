

#pragma once


#include <vector>
#include <random>
#include "SceneNode.hpp"
#include "Lego.hpp"




class ProcLegoNode : public SceneNode{
	int w, h, l;
	int pieces=0;
	bool fill=false;
//	NonhierBox bound;
	std::vector<Lego *> choices;
	std::vector<Material *> cols;
	std::vector<std::vector<std::vector<int>>> avail; //0 empty, 1 avail, 2 taken
	std::vector<std::vector<int>> indices;

	void addIndices(std::vector<int> justAdded, Lego * brick);
	bool addBrick(std::vector<int> addTo, Lego * brick, Material *);


	void generate();



public:

	ProcLegoNode(std::string name, int,int,int,std::vector<Lego *>& , std::vector<Material *>&,bool);

	Intersection * trace(glm::vec3 p, glm::vec3 u) override;

};


