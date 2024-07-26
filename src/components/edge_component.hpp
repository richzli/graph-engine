#pragma once

#include "component.hpp"

class edge_component : public component {
public:
    edge_component();
    edge_component(glm::vec3 src, glm::vec3 dst, glm::vec4 color);
    edge_component(const edge_component & ec);

    glm::vec3 get_src();
    glm::vec3 get_dst();

    void set_src(var<glm::vec3> src);
    void set_dst(var<glm::vec3> dst);
protected:
    var<glm::vec3> src, dst;
};