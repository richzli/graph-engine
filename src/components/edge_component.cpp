#include "edge_component.hpp"

edge_component::edge_component(
    glm::vec3 src,
    glm::vec3 dst,
    glm::vec4 color
) : component(color), src(src), dst(dst) { }

edge_component::edge_component() : edge_component(ZERO3, ZERO3, BLACK) { }

edge_component::edge_component(const edge_component & ec) : component(ec), src(ec.src), dst(ec.dst) { }

void edge_component::apply(std::shared_ptr<edge_component> animation) {
    this->component::apply(animation);

    for (int chan : animation->src.get_channels()) {
        if (animation->src[chan]->active) {
            this->src[chan] = animation->src[chan]->copy();
        }
    }

    for (int chan : animation->dst.get_channels()) {
        if (animation->dst[chan]->active) {
            this->dst[chan] = animation->dst[chan]->copy();
        }
    }
}