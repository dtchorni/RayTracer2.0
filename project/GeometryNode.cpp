// Fall 2018

#include "GeometryNode.hpp"

//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
	const std::string & name, Primitive *prim, Material *mat )
	: SceneNode( name )
	, m_material( mat )
	, m_primitive( prim )
{
	m_nodeType = NodeType::GeometryNode;
}

void GeometryNode::setMaterial( Material *mat )
{
	// Obviously, there's a potential memory leak here.  A good solution
	// would be to use some kind of reference counting, as in the 
	// C++ shared_ptr.  But I'm going to punt on that problem here.
	// Why?  Two reasons:
	// (a) In practice we expect the scene to be constructed exactly
	//     once.  There's no reason to believe that materials will be
	//     repeatedly overwritten in a GeometryNode.
	// (b) A ray tracer is a program in which you compute once, and 
	//     throw away all your data.  A memory leak won't build up and
	//     crash the program.

	m_material = mat;
}


glm::vec3 GeometryNode::calculateCol(Intersection intersection, std::list<Light*> sources,SceneNode *root,glm::vec3 p, glm::vec3 u, glm::vec3 ambient) {
//	std::cout<<"HI"<<std::endl;
	return m_material->getColour(intersection,sources,root,p,u,ambient);
}

Intersection *GeometryNode::trace(glm::vec3 p, glm::vec3 u) {
	glm::vec3 curr_p = glm::vec3(invtrans*glm::vec4(p,1));
	glm::vec3 curr_u = glm::vec3(invtrans*(glm::vec4(u,0)));
	Intersection * inter = m_primitive->intersect(curr_p,curr_u);
	if(inter) {
		inter->obj = this;//->m_nodeId;
	}
	for(auto child : children){
		Intersection * curr = child->trace(curr_p,curr_u);
		if(curr){
			if(inter){
				if(length(inter->point0-curr_p) > (length(curr->point0-curr_p))) inter=curr;
				else delete curr;
			}else{
				inter=curr;
			}
		}
	}

	if(inter) {
		inter->point0 = glm::vec3((trans * glm::vec4(inter->point0, 1)));
		inter->obj_norm0 = glm::normalize(glm::vec3(glm::vec4(inter->obj_norm0, 0) * (invtrans)));
		inter->point1 = glm::vec3((trans * glm::vec4(inter->point1, 1)));
		inter->obj_norm1 = glm::normalize(glm::vec3(glm::vec4(inter->obj_norm1, 0) * (invtrans)));
	}
	return inter;
}
