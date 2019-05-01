// Fall 2018

#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"
#include "SceneNode.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess);
  virtual ~PhongMaterial();

  glm::vec3 getColour(Intersection inter, std::list<Light *> sources,SceneNode * root,glm::vec3 p, glm::vec3 u,glm::vec3 ambient) override;

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;

  double m_shininess;
};
