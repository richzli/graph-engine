#pragma once

#include "component.hpp"

class line : public component {
public:
    line(glm::vec2 src, glm::vec2 dst, float width, glm::vec3 color);
    line(glm::vec2 src, glm::vec2 dst, float width);

    glm::vec2 get_src();
    glm::vec2 get_dst();
    float get_width();

    void set_src(glm::vec2 src);
    void set_dst(glm::vec2 dst);
    void set_width(float width);
protected:
    glm::vec2 src, dst;
    float width;

    virtual void init_vertices() override;
    virtual void calc_vertices() override;
};