#pragma once

#include "edge_component.hpp"

class line : public edge_component {
public:
    line(glm::vec2 src, glm::vec2 dst, float width);
    line(glm::vec3 src, glm::vec3 dst, float width, glm::vec4 color);
    line(const line & l);

    std::shared_ptr<component> copy() override;

    glm::vec3 get_center() override;

    bool hit(glm::vec2 pt) override;
    void drag(glm::vec2 d) override;

    var<float> width;

    void apply(std::shared_ptr<line> animation);

    static std::shared_ptr<shader> _shader;
protected:

    void calc_vertices() override;
    void calc_indices() override;

    std::shared_ptr<shader> get_shader() override;
    void bind_uniforms() override;
};