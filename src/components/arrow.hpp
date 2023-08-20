#pragma once

#include "line.hpp"

class arrow : public line {
public:
    arrow(glm::vec2 src, glm::vec2 dst, float width, glm::vec3 color);
    arrow(glm::vec2 src, glm::vec2 dst, float width);
protected:
    void init_vertices() override;
    void calc_vertices() override;
};