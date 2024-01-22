#include "circle.hpp"

circle::circle(
    glm::vec3 position,
    float radius,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 color
) : node_component(position, rotation, scale, color) {
    this->radius = radius;

    init_buffers();
}

circle::circle(
    glm::vec2 pos,
    float radius
) : circle(glm::vec3(pos, 0.0f), radius, ZERO3, ONE3, BLACK) { }

float circle::get_radius() const {
    return radius;
}

void circle::set_radius(float radius) {
    this->radius = radius;
    this->update_vertices();
}

void circle::calc_vertices() {
    vertices = {
        {-this->radius, -this->radius},
        { this->radius, -this->radius},
        { this->radius,  this->radius},
        {-this->radius,  this->radius},
    };
}

void circle::calc_indices() {
    indices = {
        0, 1, 2,
        2, 3, 0,
    };
}

std::shared_ptr<shader> circle::_shader = nullptr;

std::shared_ptr<shader> circle::get_shader() {
    return _shader;
}

void circle::bind_uniforms() {
    this->get_shader()->set_mat4("model", this->get_model_matrix());
    this->get_shader()->set_vec2("center", ZERO2);
    this->get_shader()->set_float("radius", this->radius);
    this->get_shader()->set_vec3("color", this->color);
}