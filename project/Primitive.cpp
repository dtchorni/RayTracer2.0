// Fall 2018

#include "Primitive.hpp"
#include "polyroots.hpp"
#include "Options.hpp"

float triangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    float magAB = glm::length(AB);
    float magAC = glm::length(AC);

    float theta = acos(glm::dot(AB, AC) / (magAB * magAC));

    return (magAB * magAC * sin(theta)) / 2;

}

Primitive::~Primitive() {
}

Sphere::Sphere() : s(glm::vec3(0), 1) {}

Sphere::~Sphere() {

}

Cube::Cube() : c(glm::vec3(0), 1) {}

Cube::~Cube() {
}

NonhierSphere::~NonhierSphere() {
}

NonhierBox::~NonhierBox() {
}

Intersection *Sphere::intersect(glm::vec3 p, glm::vec3 u) {
    return s.intersect(p, u);
}

Intersection *Cube::intersect(glm::vec3 p, glm::vec3 u) {
    return c.intersect(p, u);
}


Intersection *NonhierSphere::intersect(glm::vec3 p, glm::vec3 u) {
    glm::vec3 q = p - m_pos;
    double a = glm::dot(u, u);
    double b = 2 * glm::dot(u, q);
    double c = glm::dot(q, q) - m_radius * m_radius;

    double roots[2];


    size_t solved = quadraticRoots(a, b, c, roots);
    if (solved == 2) {
        float t[2];
        if (roots[0] < 0 && roots[1] < 0) return nullptr;
        else if (roots[0] < 0) {
            t[0] = roots[1];
            t[1] = 0;
        } else if (roots[1] < 0) {
            t[0] = roots[0];
            t[1] = 0;
        } else {
            t[0] = roots[0] < roots[1] ? roots[0] : roots[1];
            t[1] = roots[0] >= roots[1] ? roots[0] : roots[1];
        }

        glm::vec3 poi[2];
        poi[0] = p + (u * t[0]);
        poi[1] = p + (u * t[1]);

        glm::vec3 norm[2];
        norm[0] = glm::normalize(poi[0] - m_pos);
        norm[1] = glm::normalize(poi[1] - m_pos);

        return new Intersection((double *) t, (glm::vec3 *) norm, (glm::vec3 *) poi);


    } else {
        return nullptr;
    }
}

void swap(double &a, double &b) {
    double t = a;
    a = b;
    b = t;
}

glm::vec3 getSign(glm::vec3 v) {
    return glm::vec3(
            v.x < 0 ? -1 : 1,
            v.y < 0 ? -1 : 1,
            v.z < 0 ? -1 : 1
    );
}

glm::vec3 NonhierBox::gourardNorm(const int v[4], glm::vec3 poi) {
    float ABCD = m_size * m_size;
    float PAB = triangleArea(vertices[v[0]], vertices[v[1]], poi);
    float PAD = triangleArea(vertices[v[0]], vertices[v[3]], poi);
    float PBC = triangleArea(vertices[v[1]], vertices[v[2]], poi);
    float PCD = triangleArea(vertices[v[2]], vertices[v[3]], poi);

    float alpha = (PBC + PCD) / ABCD;
    float beta = (PAD + PCD) / ABCD;
    float gamma = (PAD + PAB) / ABCD;
    float phi = (PBC + PAB) / ABCD;

    return glm::normalize(
            alpha * vertexNorms[v[0]] +
            beta * vertexNorms[v[1]] +
            gamma * vertexNorms[v[2]] +
            phi * vertexNorms[v[3]]);


}

const glm::vec3 NonhierBox::norms[3] = {
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 0, 1)
};

const int NonhierBox::faces[6][4] = {
        {4, 5, 1, 0},//left
        {0, 1, 2, 3},//front
        {4, 0, 3, 7},//bottom
        {3, 2, 6, 7},//right
        {1, 5, 6, 2},//top
        {4, 5, 6, 7}//back
};

const glm::vec3 NonhierBox::vertexNorms[8]{
        glm::normalize(-norms[0] - norms[1] - norms[2]),
        glm::normalize(-norms[0] + norms[1] - norms[2]),
        glm::normalize(norms[0] + norms[1] - norms[2]),
        glm::normalize(norms[0] - norms[1] - norms[2]),
        glm::normalize(-norms[0] - norms[1] + norms[2]),
        glm::normalize(-norms[0] + norms[1] + norms[2]),
        glm::normalize(norms[0] + norms[1] + norms[2]),
        glm::normalize(norms[0] - norms[1] + norms[2]),
};

Intersection *NonhierBox::intersect(glm::vec3 p, glm::vec3 u) {

    double tmin = (min.x - p.x) / u.x;
    double tmax = (max.x - p.x) / u.x;

    if (tmin > tmax) swap(tmin, tmax);

    double tymin = (min.y - p.y) / u.y;
    double tymax = (max.y - p.y) / u.y;

    if (tymin > tymax) swap(tymax, tymin);

    if ((tmin > tymax) || (tymin > tmax)) return nullptr;

    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    double tzmin = (min.z - p.z) / u.z;
    double tzmax = (max.z - p.z) / u.z;

    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return nullptr;

    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;


    if(tmin<=0) return nullptr;

    float t[2];
    t[0] = tmin;
    t[1] = tmax;
    glm::vec3 poi[2];
    poi[0] = p + (t[0] * u);
    poi[1] = p + (t[1] * u);

    glm::vec3 center = m_pos + glm::vec3((float) (m_size / 2), (float) (m_size / 2), (float) (m_size / 2));

    glm::vec3 norm[2];
    norm[0] = glm::vec3(0);
    norm[1] = glm::vec3(0);


    if (options.gourard) {
        if (glm::dot(poi[0] - m_pos, norms[0]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[0], poi[0]);

        } else if (glm::dot(poi[0] - m_pos, norms[1]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[2], poi[0]);
        } else if (glm::dot(poi[0] - m_pos, norms[2]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[1], poi[0]);
        } else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[0]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[3], poi[0]);
        } else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[1]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[4], poi[0]);
        } else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[2]) <= 0.0001f) {
            norm[0] = gourardNorm(faces[5], poi[0]);
        }
        if (glm::dot(poi[1] - m_pos, norms[0]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[0], poi[1]);

        } else if (glm::dot(poi[1] - m_pos, norms[1]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[2], poi[1]);
        } else if (glm::dot(poi[1] - m_pos, norms[2]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[1], poi[1]);
        } else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[0]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[3], poi[1]);
        } else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[1]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[4], poi[1]);
        } else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[2]) <= 0.0001f) {
            norm[1] = gourardNorm(faces[5], poi[1]);
        }
//        norm[0] = glm::normalize(poi[0]-center);
//        norm[1] = glm::normalize(poi[1]-center);
    } else {


        if (glm::dot(poi[0] - m_pos, norms[0]) <= 0.0001f) norm[0] = -norms[0];
        else if (glm::dot(poi[0] - m_pos, norms[1]) <= 0.0001f) norm[0] = -norms[1];
        else if (glm::dot(poi[0] - m_pos, norms[2]) <= 0.0001f) norm[0] = -norms[2];
        else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[0]) <= 0.0001f) norm[0] = norms[0];
        else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[1]) <= 0.0001f) norm[0] = norms[1];
        else if (glm::dot(poi[0] - (m_pos + (float) m_size), -norms[2]) <= 0.0001f) norm[0] = norms[2];

        if (glm::dot(poi[1] - m_pos, norms[0]) <= 0.0001f) norm[1] = -norms[0];
        else if (glm::dot(poi[1] - m_pos, norms[1]) <= 0.0001f) norm[1] = -norms[1];
        else if (glm::dot(poi[1] - m_pos, norms[2]) <= 0.0001f) norm[1] = -norms[2];
        else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[0]) <= 0.0001f) norm[1] = norms[0];
        else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[1]) <= 0.0001f) norm[1] = norms[1];
        else if (glm::dot(poi[1] - (m_pos + (float) m_size), -norms[2]) <= 0.0001f) norm[1] = norms[2];

    }
    return new Intersection((double *) t, (glm::vec3 *) norm, (glm::vec3 *) poi);


}


NonhierCylinder::NonhierCylinder(float min, float max, float r, glm::vec3 pos) :
        minZ(min + pos.z), maxZ(max + pos.z), radius(r), m_pos(pos) {}

Intersection *NonhierCylinder::intersect(glm::vec3 p, glm::vec3 u) {
    glm::vec3 q = p - m_pos;
    double a = (u.x * u.x) + (u.y * u.y);
    double b = 2 * ((q.x * u.x) + (q.y * u.y));
    double c = (q.x * q.x) + (q.y * q.y) - (radius * radius);

    double roots[2];

    size_t solved = quadraticRoots(a, b, c, roots);
    float t[2];
    if (solved == 2) {
        if (roots[0] < 0 && roots[1] < 0) return nullptr;
        else {
            t[0] = roots[0] < roots[1] ? roots[0] : roots[1];
            t[1] = roots[0] >= roots[1] ? roots[0] : roots[1];
        }

        if(t[0]<0) return nullptr;

        glm::vec3 poi[2];
        poi[0] = p + (u * t[0]);
        poi[1] = p + (u * t[1]);
        glm::vec3 norm[2];
        if (poi[0].z > minZ && poi[0].z < maxZ) {
            norm[0] = glm::normalize(glm::vec3(poi[0].x, poi[0].y, 0));
//			return new Intersection(t[0],norm,poi1);
        } else if (poi[0].z < minZ && poi[1].z > minZ) {
            norm[0] = glm::vec3(0, 0, -1);
            t[0] = ((minZ - q.z) / u.z);
            poi[0] = p + (u * t[0]);
//				return new Intersection(t[0],norm,poi1);
        } else if (poi[0].z > maxZ && poi[1].z < maxZ) {
            norm[0] = glm::vec3(0, 0, 1);
            t[0] = ((maxZ - q.z) / u.z);
            poi[0] = p + (u * t[0]);
//				return new Intersection(t[0],norm,poi1);
        } else return nullptr;

        if (poi[1].z > minZ && poi[1].z < maxZ) {
            norm[1] = glm::normalize(glm::vec3(poi[1].x, poi[1].y, 0));
//			return new Intersection(t[1],norm,poi1);
        } else if (poi[1].z < minZ && poi[0].z > minZ) {
            norm[1] = glm::vec3(0, 0, -1);
            t[1] = (minZ - q.z) / u.z;
            poi[1] = p + (u * t[1]);
//				return new Intersection(t[1],norm,poi1);
        } else if (poi[1].z > maxZ && poi[0].z < maxZ) {
            norm[1] = glm::vec3(0, 0, 1);
            t[1] = (minZ - q.z) / u.z;
            poi[1] = p + (u * t[1]);
//				return new Intersection(t[1],norm,poi1);
        }//else return nullptr;





        return new Intersection((double *) t, (glm::vec3 *) norm, (glm::vec3 *) poi);


    }
    return nullptr;
}


NonhierCone::NonhierCone(float min, float max, glm::vec3 pos) :
        minZ(min), maxZ(max), m_pos(pos) {}

Intersection *NonhierCone::intersect(glm::vec3 p, glm::vec3 u) {
    glm::vec3 q = p - m_pos;
    float a = (u.x * u.x) + (u.y * u.y) - (u.z * u.z);
    float b = 2 * ((q.x * u.x) + (q.y * u.y) - (q.z * u.z));
    float c = (q.x * q.x) + (q.y * q.y) - (q.z * q.z);

    double roots[2];

    size_t solved = quadraticRoots(a, b, c, roots);

    if (solved == 2) {
        float t[0];
        if (roots[0] < 0 && roots[1] < 0) return nullptr;
        else {
            t[0] = roots[0] < roots[1] ? roots[0] : roots[1];
            t[1] = roots[0] >= roots[1] ? roots[0] : roots[1];
        }

        if(t[0]<0) return nullptr;

        glm::vec3 poi[2];
        poi[0] = p + (u * t[0]);
        poi[1] = p + (u * t[1]);
        glm::vec3 norm[2];
        if ((poi[0].z > maxZ && poi[1].z > maxZ) ||
            (poi[0].z < minZ && poi[1].z < minZ) ||
            (poi[0].z < minZ && poi[1].z > maxZ) ||
            (poi[1].z < minZ && poi[0].z > maxZ)
                ) {
            return nullptr;
        }
        if ((poi[0].z > maxZ && poi[1].z <= maxZ && t[1] > 0)) {
            norm[0] = glm::normalize(glm::vec3(poi[1].x, poi[1].y, -poi[1].z));
//			return new Intersection(t[1],norm,poi[0]);
        } else if (poi[0].z > minZ && poi[0].z < maxZ && t[0] > 0) {
            norm[0] = glm::normalize(glm::vec3(poi[0].x, poi[0].y, -poi[0].z));
//			return new Intersection(t[0],norm,poi[0]);
        } else if ( // circle
                (poi[0].z < minZ && poi[1].z > minZ)
                ) {
            norm[0] = glm::vec3(0, 0, -1);
            t[0] = t[0] + ((t[1] - t[0]) * (poi[0].z - minZ) / (poi[0].z - poi[1].z));
            poi[0] = p + (u * t[0]);
            //			return  new Intersection(t,norm,p+(u*t));
        }

        if ((poi[1].z > maxZ && poi[0].z > maxZ) ||
            (poi[1].z < minZ && poi[0].z < minZ) ||
            (poi[1].z < minZ && poi[0].z > maxZ) ||
            (poi[0].z < minZ && poi[1].z > maxZ)
                ) {
            return nullptr;
        }
        if ((poi[1].z > maxZ && poi[0].z <= maxZ && t[0] > 0)) {
            norm[1] = glm::normalize(glm::vec3(poi[0].x, poi[0].y, -poi[0].z));
//			return new Intersection(t[1],norm,poi[1]);
        } else if (poi[1].z > minZ && poi[1].z < maxZ && t[1] > 0) {
            norm[1] = glm::normalize(glm::vec3(poi[1].x, poi[1].y, -poi[1].z));
//			return new Intersection(t[0],norm,poi[1]);
        } else if ( // circle
                (poi[1].z < minZ && poi[0].z > minZ)
                ) {
            norm[1] = glm::vec3(0, 0, -1);
            t[1] = t[1] + ((t[0] - t[1]) * (poi[1].z - minZ) / (poi[1].z - poi[0].z));
            poi[1] = p + (u * t[1]);
//			return  new Intersection(t,norm,p+(u*t));
        }

        return new Intersection((double *) t, (glm::vec3 *) norm, (glm::vec3 *) poi);

    }
    return nullptr;
}

NonhierCone::~NonhierCone() {}


Cylinder::Cylinder() : c(-0.5, 0.5, 1.0, glm::vec3(0)) {

}

Intersection *Cylinder::intersect(glm::vec3 p, glm::vec3 u) {
    return c.intersect(p, u);
}

Cylinder::~Cylinder() {}

