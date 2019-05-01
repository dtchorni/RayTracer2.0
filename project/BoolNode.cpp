//
// Created by dtchorni on 24/11/18.
//

#include <vector>
#include "BoolNode.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <map>
#include "cs488-framework/MathUtils.hpp"
#include "Options.hpp"


BoolNode::BoolNode(const std::string &name, int type) :
        SceneNode(name),
        booltype(type == 0 ? BoolType::Union : type == 1 ? BoolType::Intersect : BoolType::Difference) {
    assert(type <= 2 && type >= 0);
    if (options.unionAll) booltype = BoolType::Union;
}


Intersection *BoolNode::_union(std::vector<Intersection *> &inters, glm::vec3 p, glm::vec3 u) {
    Intersection *toReturn = nullptr;
    for (auto i : inters) {
        if (i) {
            if (toReturn) {
                if (glm::length(i->point0 - p) < glm::length(toReturn->point0 - p)) {
                    toReturn = i;
                }
            } else {
                toReturn = i;
            }
        }
    }
    if (toReturn) return new Intersection(*toReturn);
    else return nullptr;
}

Intersection *BoolNode::_intersect(std::vector<Intersection *> &inters, glm::vec3 p, glm::vec3 u) {
    if (std::find(inters.begin(), inters.end(), nullptr) != inters.end()) return nullptr;
    GeometryNode *obj = inters[0]->obj;
    std::vector<std::pair<double, double>> t_range;
    for (auto i : inters) {
        if (i) {
            t_range.emplace_back(std::pair<double, double>(
                    (p.x + i->point0.x) / (u.x),
                    (p.x + i->point1.x) / (u.x)
            ));
        }
    }
    std::pair<double, double> first_obj = t_range[0];
    glm::vec3 poi[2];
    glm::vec3 norm[2] = {inters[0]->obj_norm0, inters[0]->obj_norm1};
    double t[2] = {first_obj.first, first_obj.second};
    for (int i = 1; i < inters.size(); ++i) {
        if (inters[i]) {
            std::pair<double, double> curr = t_range[i];
            if ((curr.first <= t[0] && curr.second <= t[0]) ||
                (curr.first >= t[1] && curr.second >= t[1]))
                return nullptr;
            else if (curr.first < t[0] && curr.second < t[1] && curr.second > t[0]) {
                t[1] = curr.second;
                norm[1] = inters[i]->obj_norm1;
            } else if (curr.first > t[0] && curr.second > t[1] && curr.first < t[1]) {
                t[0] = curr.first;
                norm[0] = inters[i]->obj_norm0;
                obj = inters[i]->obj;
            } else if (curr.first > t[0] && curr.second < t[1]) {
                t[0] = curr.first;
                t[1] = curr.second;
                norm[0] = inters[i]->obj_norm0;
                norm[1] = inters[i]->obj_norm1;
                obj = inters[i]->obj;

            }
        }
    }
    if (first_obj.first == t[0]) norm[0] = inters[0]->obj_norm0;
    if (first_obj.second == t[1]) norm[1] = inters[0]->obj_norm1;

    poi[0] = p + (t[0] * u);
    poi[1] = p + (t[1] * u);

    Intersection *toReturn = new Intersection(t, norm, poi);
    toReturn->obj = obj;
    return toReturn;

}

Intersection *BoolNode::_difference(std::vector<Intersection *> &inters, glm::vec3 p, glm::vec3 u) {
    if (inters[0] == nullptr) return nullptr;
    GeometryNode *obj = inters[0]->obj;
    std::vector<std::pair<double, double>> t_range;
    for (auto i : inters) {
        if (i) {
            t_range.emplace_back(std::pair<double, double>(
                    (p.x + i->point0.x) / (u.x),
                    (p.x + i->point1.x) / (u.x)
            ));
        }
    }
    std::pair<double, double> first_obj = t_range[0];
    glm::vec3 poi[2] = {inters[0]->point0, inters[0]->point1};
    glm::vec3 norm[2] = {inters[0]->obj_norm0, inters[0]->obj_norm1};
    double t[2] = {first_obj.first, first_obj.second};
    for (int i = 1; i < inters.size(); ++i) {
        if (inters[i]) {
            std::pair<double, double> curr = t_range[i];
            if (curr.first <= t[0] && curr.second >= t[1]) return nullptr;
            else if (curr.first < t[0] && curr.second < t[1]) {
                t[0] = curr.second;
                poi[0]= inters[i]->point1;
                norm[0] = -inters[i]->obj_norm1;
                obj = inters[i]->obj;
            } else if (curr.first > t[0] && curr.second > t[1]) {
                t[1] = curr.first;
                poi[1] = inters[i]->point0;
                norm[1] = inters[i]->obj_norm0;
            }
        }
    }
    /*if (first_obj.first == t[0]) norm[0] = inters[0]->obj_norm0;
    if (first_obj.second == t[1]) norm[1] = inters[0]->obj_norm1;

    poi[0] = p + (t[0] * u);
    poi[1] = p + (t[1] * u);*/

    Intersection *toReturn = new Intersection(t, norm, poi);
    toReturn->obj = obj;
    return toReturn;

}

Intersection *BoolNode::trace(glm::vec3 p, glm::vec3 u) {
    std::vector<Intersection *> inters;
    for (auto child : children) {
        Intersection *curr = child->trace(glm::vec3(invtrans * glm::vec4(p, 1)),
                                          glm::vec3(invtrans * glm::vec4(u, 0)));
        if (curr) {
            curr->point0 = glm::vec3((trans * glm::vec4(curr->point0, 1)));
            curr->obj_norm0 = glm::vec3(glm::vec4(curr->obj_norm0, 0) * (invtrans));
            curr->point1 = glm::vec3((trans * glm::vec4(curr->point1, 1)));
            curr->obj_norm1 = glm::vec3(glm::vec4(curr->obj_norm1, 0) * (invtrans));
        }
        inters.emplace_back(curr);
    }

    Intersection *toReturn = nullptr;

    switch (booltype) {
        case (BoolType::Union) :
            toReturn = _union(inters, p, u);
            break;
        case (BoolType::Difference):
            toReturn = _difference(inters, p, u);
            break;
        case (BoolType::Intersect):
            toReturn = _intersect(inters, p, u);
            break;
        default:
            toReturn = nullptr;
            break;
    }
    for (auto i : inters) if (i) delete i;

    return toReturn;
}

