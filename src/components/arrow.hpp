#pragma once

#include "line.hpp"

class arrow : public line {
public:
    arrow(glm::vec2 src, glm::vec2 dst, float width, glm::vec4 color);
    arrow(glm::vec2 src, glm::vec2 dst, float width);
    arrow(const arrow & a);

    std::shared_ptr<component> copy() override;
protected:
    void calc_vertices() override;
    void calc_indices() override;
};