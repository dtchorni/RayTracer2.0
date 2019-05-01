

#include "ProcLegoNode.hpp"
#include "GeometryNode.hpp"
#include "Options.hpp"

ProcLegoNode::ProcLegoNode(std::string name, int a, int b, int c, std::vector<Lego *> &o, std::vector<Material *> &col,
						   bool f)
		:
		SceneNode(name), w(a), l(b), h(c), choices(o), cols(col), indices(), fill(f),
			  avail(a, std::vector<std::vector<int>>(b, std::vector<int>(c, 0))) {

	generate();
}

void ProcLegoNode::addIndices(std::vector<int> justAdded, Lego *brick) {
	if (justAdded[2] + 1 < h &&
		avail[justAdded[0]][justAdded[1]][justAdded[2] + 1] == 0) {
		std::vector<int> index = {justAdded[0], justAdded[1], justAdded[2] + 1};
		indices.push_back(index);
		avail[justAdded[0]][justAdded[1]][justAdded[2] + 1] = 1;

	}
}

bool ProcLegoNode::addBrick(std::vector<int> addTo, Lego *brick, Material *col) {

	GeometryNode * spot = new GeometryNode("brick: " + std::to_string(pieces), brick, col);
	glm::vec3 trans = glm::vec3(5 * addTo[0], 6 * addTo[2], 5 * addTo[1]);
	spot->translate(trans);
	this->add_child(spot);
	addIndices(addTo, brick);

	return true;
}

void ProcLegoNode::generate() {
	std::mt19937 gen;
	gen.seed(0);

	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < l; ++j) {
			avail[i][j][0] = 1;
			std::vector<int> index = {i, j, 0};
			indices.push_back(index);
		}
	}

	std::uniform_int_distribution<unsigned int> _size((w * l * h) / 2, (w * l * h));
	int num_pieces = fill ? (w * l * h) : _size(gen);

	while (pieces < num_pieces) {
		std::uniform_int_distribution<unsigned int> _randPos(0, indices.size() - 1);
		std::uniform_int_distribution<unsigned int> _randBrick(0, choices.size() - 1);
		std::uniform_int_distribution<unsigned int> _randCols(0, cols.size() - 1);
		int i = _randPos(gen);
		Lego *toInsert = choices.at(_randBrick(gen));
		std::vector<int> insertTo = indices.at(i);
		indices.erase(indices.begin() + i);
		Material *col = cols.at(_randCols(gen));
		while (!addBrick(insertTo, toInsert, col)) {}
		avail[insertTo[0]][insertTo[1]][insertTo[2]] = 2;
		++pieces;
	}

}


Intersection *ProcLegoNode::trace(glm::vec3 p, glm::vec3 u) {
	return SceneNode::trace(p,u);
}