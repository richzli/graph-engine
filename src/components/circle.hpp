#pragma once

#include "node_component.hpp"

class circle : public node_component {
public:
    circle(glm::vec3 position, float radius, glm::vec3 rotation, glm::vec3 scale, glm::vec3 offset, glm::vec4 color);
    circle(glm::vec2 pos, float radius);
    circle(const circle & c);

    std::shared_ptr<component> copy() override;

    glm::vec3 get_center() override;
    glm::vec3 get_border(glm::vec3 direction) override;

    float get_radius();

    void set_radius(float radius);

    bool hit(glm::vec2 pt) override;
    void drag(glm::vec2 d) override;

    static std::shared_ptr<shader> _shader;
protected:
    var<float> radius;

    void calc_vertices() override;
    void calc_indices() override;

    std::shared_ptr<shader> get_shader() override;

    void bind_uniforms() override;
};