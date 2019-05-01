// Fall 2018

#include "SceneNode.hpp"

#include "cs488-framework/MathUtils.hpp"

#include <iostream>
#include <sstream>

using namespace std;

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;


// Static class variable
unsigned int SceneNode::nodeInstanceCount = 0;


//---------------------------------------------------------------------------------------
SceneNode::SceneNode(const std::string &name)
		: m_name(name),
		  m_nodeType(NodeType::SceneNode),
		  trans(mat4(1)),
		  invtrans(mat4(1)),
		  m_nodeId(nodeInstanceCount++) {

}

//---------------------------------------------------------------------------------------
// Deep copy
SceneNode::SceneNode(const SceneNode &other)
		: m_nodeType(other.m_nodeType),
		  m_name(other.m_name),
		  trans(other.trans),
		  invtrans(other.invtrans) {
	for (SceneNode *child : other.children) {
		this->children.push_front(new SceneNode(*child));
	}
}

//---------------------------------------------------------------------------------------
SceneNode::~SceneNode() {
	for (SceneNode *child : children) {
		delete child;
	}
}

//---------------------------------------------------------------------------------------
void SceneNode::set_transform(const glm::mat4 &m) {
	trans = m;
	invtrans = glm::inverse(m);
}

//---------------------------------------------------------------------------------------
const glm::mat4 &SceneNode::get_transform() const {
	return trans;
}

//---------------------------------------------------------------------------------------
const glm::mat4 &SceneNode::get_inverse() const {
	return invtrans;
}

//---------------------------------------------------------------------------------------
void SceneNode::add_child(SceneNode *child) {
	children.push_back(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::remove_child(SceneNode *child) {
	children.remove(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::rotate(char axis, float angle) {
	vec3 rot_axis;

	switch (axis) {
		case 'x':
			rot_axis = vec3(1, 0, 0);
			break;
		case 'y':
			rot_axis = vec3(0, 1, 0);
			break;
		case 'z':
			rot_axis = vec3(0, 0, 1);
			break;
		default:
			break;
	}
	mat4 rot_matrix = glm::rotate(degreesToRadians(angle), rot_axis);
	set_transform(rot_matrix * trans);
}

//---------------------------------------------------------------------------------------
void SceneNode::scale(const glm::vec3 &amount) {
	set_transform(glm::scale(amount) * trans);
}

//---------------------------------------------------------------------------------------
void SceneNode::translate(const glm::vec3 &amount) {
	set_transform(glm::translate(amount) * trans);
}


//---------------------------------------------------------------------------------------
int SceneNode::totalSceneNodes() const {
	return nodeInstanceCount;
}

//---------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const SceneNode &node) {

	//os << "SceneNode:[NodeType: ___, name: ____, id: ____, isSelected: ____, transform: ____"
	switch (node.m_nodeType) {
		case NodeType::SceneNode:
			os << "SceneNode";
			break;
		case NodeType::GeometryNode:
			os << "GeometryNode";
			break;
		case NodeType::JointNode:
			os << "JointNode";
			break;
	}
	os << ":[";

	os << "name:" << node.m_name << ", ";
	os << "id:" << node.m_nodeId;

	os << "]\n";
	return os;
}

Intersection *SceneNode::trace(glm::vec3 p, glm::vec3 u) {
	Intersection *inter = nullptr;
	glm::vec3 curr_p = glm::vec3(invtrans * glm::vec4(p, 1));
	glm::vec3 curr_u = glm::vec3(invtrans * glm::vec4(u, 0));
	for (auto child : children) {
		Intersection *curr = child->trace(curr_p, curr_u);
		if (curr) {
			if (inter) {
//				cout << "Closest: " << ((SceneNode *) inter->obj)->m_name << " : " << length(inter->point0 - curr_p)
//					 << " check - " << ((SceneNode *) curr->obj)->m_name << " : " << (length(curr->point0 - curr_p))
//					 << endl;
				if (length(inter->point0 - curr_p) > (length(curr->point0 - curr_p))) inter = curr;
				else delete curr;
			} else {
				inter = curr;
			}
		}
	}
	if (inter) {
		inter->point0 = glm::vec3((trans * glm::vec4(inter->point0, 1)));
		inter->obj_norm0 = glm::normalize(glm::vec3(glm::vec4(inter->obj_norm0, 0) * (invtrans)));
		inter->point1 = glm::vec3((trans * glm::vec4(inter->point1, 1)));
		inter->obj_norm1 = glm::normalize(glm::vec3(glm::vec4(inter->obj_norm1, 0) * (invtrans)));
	}
	return inter;
}

SceneNode *SceneNode::findNode(unsigned int id) {
	if (id == m_nodeId) return this;
	for (auto child : children) {
		SceneNode * ret = child->findNode(id);
		if (ret) return ret;
	}
	return nullptr;
}
