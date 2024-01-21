#pragma once

#include "node_component.hpp"

class circle : public node_component {
public:
    circle(glm::vec3 position, float radius, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
    circle(glm::vec2 pos, float radius);

    float get_radius() const;

    void set_radius(float radius);

    static std::shared_ptr<shader> _shader;
protected:
    float radius;

    void calc_vertices() override;
    void calc_indices() override;

    std::shared_ptr<shader> get_shader() override;

    void bind_uniforms() override;
};