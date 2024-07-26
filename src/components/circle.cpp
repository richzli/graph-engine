#include "circle.hpp"

circle::circle(
    glm::vec3 position,
    float radius,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 offset,
    glm::vec4 color
) : node_component(position, rotation, scale, offset, color), radius(radius) {
    init_buffers();
}

circle::circle(
    glm::vec2 pos,
    float radius
) : circle(glm::vec3(pos, 0.0f), radius, ZERO3, ONE3, ZERO3, BLACK) { }

circle::circle(const circle & c) : node_component(c), radius(c.radius) {
    init_buffers();
}

std::shared_ptr<component> circle::copy() {
    return std::make_shared<circle>(*this);
}

glm::vec3 circle::get_center() {
    return this->get_position();
}

glm::vec3 circle::get_border(glm::vec3 direction) {
    if (direction == ZERO3) {
        return this->get_position();
    }
    return this->get_position() + glm::normalize(direction) * (this->radius - 3.0f);
}

float circle::get_radius() {
    return radius;
}

void circle::set_radius(float radius) {
    this->radius = radius;
}

bool circle::hit(glm::vec2 pt) {
    return glm::length2(get_position() - glm::vec3(pt, 0.0f)) <= radius * radius;
}

void circle::drag(glm::vec2 d) {
    this->set_position(this->get_position() + glm::vec3(d, 0.0f));
}

void circle::calc_vertices() {
    vertices = {
        {-this->radius, -this->radius, 0.0f},
        { this->radius, -this->radius, 0.0f},
        { this->radius,  this->radius, 0.0f},
        {-this->radius,  this->radius, 0.0f},
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
    this->get_shader()->set_vec4("color", this->color);
}