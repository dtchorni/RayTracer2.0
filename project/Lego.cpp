
#include "Lego.hpp"
#include "BoolNode.hpp"
#include "GeometryNode.hpp"


Lego::Lego(int a, int b, bool c) : w(a), l(b), flat(c) {
	construct();
}

Intersection *Lego::intersect(glm::vec3 p, glm::vec3 u) {
	return brick->trace(p, u);
}

Lego::Lego(const Lego &o) :
		w(o.w), l(o.l), flat(o.flat), brick(o.brick) {}

Lego::~Lego() {
	delete brick;
}

void Lego::construct() {
	brick = new SceneNode("brick");
	if (w == 1 && l == 1 && !flat) {
		GeometryNode * body = new GeometryNode("body",
											   new NonhierBox(glm::vec3(-3.0f, -3.0f, -3.0f), 6.0));
		body->scale(glm::vec3(5.0f / 6.0f, 1.0f, 5.0f / 6.0f));
		GeometryNode * top = new GeometryNode("top",
											  new NonhierCylinder(-1.0, 0.4, 1.5, glm::vec3(0.0f, 0.0f, 0.0f)));
		top->rotate('x', 90);
		top->translate(glm::vec3(0.0f, 3.0f, 0.0f));

		BoolNode * uni = new BoolNode("uni", 0);
		uni->add_child(body);
		uni->add_child(top);

		GeometryNode * inside = new GeometryNode("inside",
												 new NonhierBox(glm::vec3(-2.5f, -2.5f, -2.5f), 5.0));

		inside->scale(glm::vec3(3.0f / 5.0f, 1.0f, 3.0f / 5.0f));
		inside->translate(glm::vec3(0.0f, -1.0f, -0.1f));

		BoolNode * diff = new BoolNode("diff", 2);
		diff->add_child(uni);
		diff->add_child(inside);
		brick->add_child(diff);
	}

}
