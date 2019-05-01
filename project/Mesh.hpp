// Fall 2018

#pragma once

#include <vector>
#include <iosfwd>
#include <string>

#include <glm/glm.hpp>

#include "Primitive.hpp"

struct Triangle
{
    size_t v1;
    size_t v2;
    size_t v3;

//    glm::vec3 norm;

    Triangle( size_t pv1, size_t pv2, size_t pv3 )
            : v1( pv1 )
            , v2( pv2 )
            , v3( pv3 )
    {}

//    void setNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    Intersection * intersect(glm::vec3 p, glm::vec3 u,glm::vec3 v1,glm::vec3 v2 ,glm::vec3 v3,
            glm::vec3 n1, glm::vec3 n2, glm::vec3 n3, bool interpolate);
};

// A polygonal mesh.
class Mesh : public Primitive {
public:
    Mesh( const std::string& fname , bool interpolate);
    NonhierSphere bound;


    Intersection * intersect(glm::vec3 o ,glm::vec3 d);

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<Triangle> m_faces;
    std::vector<glm::vec3> m_vertex_normals;
    bool interpolateNorms;
    glm::vec3 gourardShadeNorm(int, int, int, Intersection *i);

    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};
