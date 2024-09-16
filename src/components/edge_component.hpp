#pragma once

#include "component.hpp"

class edge_component : public component {
public:
    edge_component();
    edge_component(glm::vec3 src, glm::vec3 dst, glm::vec4 color);
    edge_component(const edge_component & ec);

    var<glm::vec3> src, dst;

    void apply(std::shared_ptr<edge_component> animation);
};