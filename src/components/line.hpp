#pragma once

#include "edge_component.hpp"

class line : public edge_component {
public:
    line(glm::vec2 src, glm::vec2 dst, float width);
    line(glm::vec2 src, glm::vec2 dst, float width, glm::vec3 color);
    line(const line & l);

    std::shared_ptr<component> copy() override;

    float get_width();

    void set_width(float width);

    bool hit(glm::vec2 pt) override;
    void drag(glm::vec2 d) override;

    static std::shared_ptr<shader> _shader;
protected:
    float width;

    void calc_vertices() override;
    void calc_indices() override;

    std::shared_ptr<shader> get_shader() override;
    void bind_uniforms() override;
};