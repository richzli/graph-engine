#include "edge_component.hpp"

edge_component::edge_component(
    glm::vec3 src,
    glm::vec3 dst,
    glm::vec4 color
) : component(color), src(src), dst(dst) { }

edge_component::edge_component() : edge_component(ZERO3, ZERO3, BLACK) { }

edge_component::edge_component(const edge_component & ec) : component(ec), src(ec.src), dst(ec.dst) { }

glm::vec3 edge_component::get_src() {
    return src;
}

glm::vec3 edge_component::get_dst() {
    return dst;
}

void edge_component::set_src(var<glm::vec3> src) {
    this->src = src;
}

void edge_component::set_dst(var<glm::vec3> dst) {
    this->dst = dst;
}
