#include "edge_component.hpp"

edge_component::edge_component(
    glm::vec2 src,
    glm::vec2 dst,
    glm::vec3 color
) : component() {
    this->src = src;
    this->dst = dst;
    this->color = color;
}

edge_component::edge_component() : edge_component(ZERO2, ZERO2, BLACK) { }

glm::vec2 edge_component::get_src() const {
    return src;
}

glm::vec2 edge_component::get_dst() const {
    return dst;
}

glm::vec3 edge_component::get_color() const {
    return color;
}

void edge_component::set_src(glm::vec2 src) {
    this->src = src;
}

void edge_component::set_dst(glm::vec2 dst) {
    this->dst = dst;
}

void edge_component::set_color(glm::vec3 color) {
    this->color = color;
}
