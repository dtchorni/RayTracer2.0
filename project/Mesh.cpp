// Fall 2018

#include <iostream>
#include <fstream>
#include "Options.hpp"
#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"




Intersection * Triangle::intersect(glm::vec3 p, glm::vec3 u, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
									glm::vec3 n1 , glm::vec3 n2, glm::vec3 n3,bool interpolate){

	glm::vec3 A = v2-v1;
	glm::vec3 B = v3-v1;
	glm::vec3 cross= glm::cross(u,B);
	double ang = glm::dot(cross,A);
	if(ang<0.000001) return nullptr;

	glm::vec3 t_orig = p-v1;
	double coeff = glm::dot(cross,t_orig)/ang;
	if(coeff < 0 || coeff>1) return nullptr;

	cross = glm::cross(t_orig,A);
	double coeff2 = glm::dot(u,cross)/ang;
	if(coeff2<0 || coeff+coeff2 >1) return nullptr;

	float t1= glm::dot(B,cross)/ang;

	if(t1 < 0) return nullptr;

	float t[2];
	t[0] = t1;
	t[1] = 0;

	glm::vec3 poi[2];
	poi[0] = p + (t[0]*u);
	poi[1] = p + (t[0]*u);
	glm::vec3 norm[2];
	if(options.gourard&& interpolate ) {
		float ABC = triangleArea(v1, v2, v3);
		float ABP = triangleArea(v1, v2, poi[0]);
		float APC = triangleArea(v1, poi[0], v3);
		float PBC = triangleArea(poi[0], v2, v3);

		float alpha = PBC / ABC;
		float beta = APC / ABC;
		float gamma = ABP / ABC;

		norm[0] = glm::normalize(alpha*n1+beta*n2+gamma*n3);
	}else{
		norm[0]=glm::cross(A,B);
	}
	return new Intersection((double*)t,(glm::vec3 *) norm ,(glm::vec3*)poi);

}

//void Triangle::setNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
//
//
//}

Mesh::Mesh( const std::string& fname, bool interpolate )
	: m_vertices()
	, m_faces() , interpolateNorms(interpolate)
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	float minx, miny, minz, maxx,maxy,maxz;
	minx=miny=minz=INFINITY;
	maxx=maxy=maxz=-INFINITY;
	
	
	
	std::ifstream ifs( "Assets/" +fname );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			if(vx<minx) minx=vx;
			if(vx>maxx) maxx=vx;
            if(vy<miny) miny=vy;
            if(vy>maxy) maxy=vy;
            if(vz<minz) minz=vz;
            if(vz>maxz) maxz=vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
			m_vertex_normals.push_back(glm::vec3(0));
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
			glm::vec3 norm = glm::cross(
					m_vertices[s2-1]-m_vertices[s1-1],
					m_vertices[s3-1]-m_vertices[s1-1]);
			m_vertex_normals[s1-1]+=norm;
			m_vertex_normals[s2-1]+=norm;
			m_vertex_normals[s3-1]+=norm;

		}
	}

    for(int i =0; i < m_vertex_normals.size(); ++i){
        m_vertex_normals[i]-glm::normalize(m_vertex_normals[i]);
    }

	glm::vec3 pos = glm::vec3(
			(maxx+minx)/2,
			(maxy+miny)/2,
			(maxz+minz)/2
			);

	float radius = glm::length(glm::vec3(maxx,maxy,maxz)-glm::vec3(minx,miny,minz))/1.88;

	bound = NonhierSphere(pos,radius);

}


std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";

  out << "}";
  return out;
}



glm::vec3 Mesh::gourardShadeNorm(int a, int b, int c, Intersection *i) {
	glm::vec3 A = m_vertices[a];
	glm::vec3 B = m_vertices[b];
	glm::vec3 C = m_vertices[c];
	float ABC = triangleArea(A,B,C);
	float ABP = triangleArea(A,B,i->point0);
	float APC = triangleArea(A,i->point0,C);
	float PBC = triangleArea(i->point0,B,C);

	float alpha = PBC/ABC;
	float beta = APC/ABC;
	float gamma = ABP/ABC;

	return glm::normalize(alpha*m_vertex_normals[a]+beta*m_vertex_normals[b]+gamma*m_vertex_normals[c]);


}


Intersection * Mesh::intersect(glm::vec3 o, glm::vec3 d) {
	Intersection * ret = nullptr;
	ret=bound.intersect(o,d);
	if(options.bound) return ret;
	if(ret) {
		delete ret;
		ret= nullptr;
		for (auto t : m_faces) {
			Intersection *cur = nullptr;
			cur = t.intersect(o, d, m_vertices[t.v1], m_vertices[t.v2], m_vertices[t.v3],
							m_vertex_normals[t.v1],m_vertex_normals[t.v2],m_vertex_normals[t.v3],interpolateNorms);
			if (cur) {
				if (ret) {
					if (cur->t0 < ret->t0) {
						delete ret;
						ret = cur;
					} else {
						delete cur;
					}
				} else {
					ret = cur;
				}
			}
		}
	}
	return ret;
}