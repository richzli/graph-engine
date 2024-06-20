#pragma once

#include "component.hpp"

class edge_component : public component {
public:
    edge_component();
    edge_component(glm::vec2 src, glm::vec2 dst, glm::vec3 color);
    edge_component(const edge_component & ec);

    glm::vec2 get_src() const;
    glm::vec2 get_dst() const;

    void set_src(glm::vec2 src);
    void set_dst(glm::vec2 dst);
protected:
    glm::vec2 src, dst;
};