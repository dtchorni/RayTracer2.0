// Fall 2018

#pragma once

#include <include/glm/vec3.hpp>
#include "Light.hpp"
#include "Primitive.hpp"
#include <list>


class SceneNode;

class Material {
public:
  virtual ~Material();
  virtual glm::vec3 getColour(Intersection inter, std::list<Light *> sources,SceneNode* root,glm::vec3 p, glm::vec3 u,glm::vec3 amb)=0;
protected:
  Material();
};
