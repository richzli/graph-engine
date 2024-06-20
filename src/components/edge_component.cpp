#include "edge_component.hpp"

edge_component::edge_component(
    glm::vec2 src,
    glm::vec2 dst,
    glm::vec3 color
) : component(color) {
    this->src = src;
    this->dst = dst;
}

edge_component::edge_component() : edge_component(ZERO2, ZERO2, BLACK) { }

edge_component::edge_component(const edge_component & ec) : component(ec) {
    this->src = ec.src;
    this->dst = ec.dst;
}

glm::vec2 edge_component::get_src() const {
    return src;
}

glm::vec2 edge_component::get_dst() const {
    return dst;
}

void edge_component::set_src(glm::vec2 src) {
    this->src = src;
    this->update_vertices();
}

void edge_component::set_dst(glm::vec2 dst) {
    this->dst = dst;
    this->update_vertices();
}
