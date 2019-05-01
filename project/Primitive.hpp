// Fall 2018

#pragma once

#include <glm/glm.hpp>
//#include "Material.hpp"
//#include "GeometryNode.hpp"

class GeometryNode;

float triangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);

struct Intersection{
	double t0, t1;
	glm::vec3 obj_norm0;
	glm::vec3 obj_norm1;
	glm::vec3 point0;
	glm::vec3 point1;
//	int objID=-1;
	GeometryNode * obj = nullptr;
	Intersection(){}
	Intersection(const double a[2], const glm::vec3 n[2], const glm::vec3 p[2])
	{
		t0 = a[0];
		t1 = a[1];
		obj_norm0=n[0];
		obj_norm1=n[1];
		point0=p[0];
		point1=p[1];
	}
	/*Intersection(const Intersection& o): Intersection(o.t,o.obj_norm,o.point) {
		obj=o.obj;
	}
	Intersection(Intersection&& o) noexcept{
		t[0] = o.t[0];
		t[1] = o.t[1];
		obj_norm[0]=o.obj_norm[0];
		obj_norm[1]=o.obj_norm[1];
		point[0]=o.point[0];
		point[1]=o.point[1];
		obj=o.obj;
		o.obj= nullptr;
	}

	Intersection& operator=(const Intersection & o){
		t[0] = o.t[0];
		t[1] = o.t[1];
		obj_norm[0]=o.obj_norm[0];
		obj_norm[1]=o.obj_norm[1];
		point[0]=o.point[0];
		point[1]=o.point[1];
		obj=o.obj;

		return *this;
	}

	Intersection& operator=(Intersection&& o) noexcept {
		t[0] = o.t[0];
		t[1] = o.t[1];
		obj_norm[0]=o.obj_norm[0];
		obj_norm[1]=o.obj_norm[1];
		point[0]=o.point[0];
		point[1]=o.point[1];
		obj=o.obj;
		o.obj= nullptr;
		return *this;
	}


	~Intersection(){}*/
};

class Primitive {
public:
	virtual Intersection * intersect(glm::vec3 p, glm::vec3 u)=0;
	virtual ~Primitive();
};


class NonhierSphere : public Primitive {
public:
    NonhierSphere(){}
	NonhierSphere(const glm::vec3& pos, double radius)
			: m_pos(pos), m_radius(radius)
	{
	}
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;
	virtual ~NonhierSphere();

private:
	glm::vec3 m_pos;
	double m_radius;
};

class NonhierBox : public Primitive {

public:
	static const glm::vec3 norms [3];
    static const int faces [6][4];
    glm::vec3 vertices [8];
    static const glm::vec3 vertexNorms [8];


	NonhierBox(const glm::vec3& pos, double size)
			: m_pos(pos), m_size(size)
	{
		min=glm::vec3(
				pos.x< pos.x+size ? pos.x : pos.x+size,
				pos.y< pos.y+size ? pos.y : pos.y+size,
				pos.z< pos.z+size ? pos.z : pos.z+size
				);
		max=glm::vec3(
				pos.x>= pos.x+size ? pos.x : pos.x+size,
				pos.y>= pos.y+size ? pos.y : pos.y+size,
				pos.z>= pos.z+size ? pos.z : pos.z+size
				);
        vertices[0] = pos;
        vertices[1] = glm::vec3(pos.x,pos.y+size,pos.z);
        vertices[2] = glm::vec3(pos.x+size,pos.y+size,pos.z);
        vertices[3] = glm::vec3(pos.x+size,pos.y,pos.z);
        vertices[4] = glm::vec3(pos.x,pos.y,pos.z+size);
        vertices[5] = glm::vec3(pos.x,pos.y+size,pos.z+size);
        vertices[6] = glm::vec3(pos.x+size,pos.y+size,pos.z+size);
        vertices[7] = glm::vec3(pos.x+size,pos.y,pos.z+size);

	}

	glm::vec3 gourardNorm(const int v[4], glm::vec3 poi);

	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;
	virtual ~NonhierBox();

private:
	glm::vec3 min, max;
	glm::vec3 m_pos;
	double m_size;

};

class NonhierCylinder : public Primitive{
	float minZ, maxZ;
	float radius;
	glm::vec3 m_pos;
public:
	NonhierCylinder(float min, float max, float r, glm::vec3);
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;
	virtual ~NonhierCylinder(){}

};

class NonhierCone : public Primitive {
	glm::vec3 m_pos;
	float minZ, maxZ;

public:

	NonhierCone(float min, float max, glm::vec3 pos);
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;

	virtual ~NonhierCone();
};

class Sphere : public Primitive {
	NonhierSphere s;
public:
	Sphere();
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;

	virtual ~Sphere();
};

class Cube : public Primitive {
	NonhierBox c;
public:
	Cube();
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;

	virtual ~Cube();
};

class Cylinder : public Primitive{
	NonhierCylinder c;
public:
	Cylinder();
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;

	virtual ~Cylinder();
};

class Cone : public Primitive {
public:
	Cone();
	Intersection * intersect(glm::vec3 p, glm::vec3 u) override;
	virtual ~Cone();


};

