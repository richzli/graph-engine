#pragma once

#include "node_component.hpp"

class circle : public node_component {
public:
    circle(glm::vec3 position, float radius, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
    circle(glm::vec2 pos, float radius);
    circle(const circle & c);

    std::shared_ptr<component> copy() override;

    glm::vec2 get_center() const override;

    float get_radius() const;

    void set_radius(float radius);

    bool hit(glm::vec2 pt) override;
    void drag(glm::vec2 d) override;

    static std::shared_ptr<shader> _shader;
protected:
    float radius;

    void calc_vertices() override;
    void calc_indices() override;

    std::shared_ptr<shader> get_shader() override;

    void bind_uniforms() override;
};