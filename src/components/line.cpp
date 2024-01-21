#include "line.hpp"

line::line(
    glm::vec2 src,
    glm::vec2 dst,
    float width,
    glm::vec3 color
) : edge_component(src, dst, color) {
    this->width = width;

    init_buffers();
}

line::line(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : line(src, dst, width, BLACK) { }

float line::get_width() {
    return width;
}

void line::set_width(float width) {
    this->width = width;
    update_vertices();
}

void line::calc_vertices() {
    float dist = glm::length(dst - src);
    glm::vec2 v = glm::normalize(dst - src);
    if (dist == 0) v = ZERO2;
    glm::vec2 perp(v.y, -v.x);
    vertices = {
        src + perp * (width/2), 
        src - perp * (width/2),
        dst - perp * (width/2),
        dst + perp * (width/2),
    };
}

void line::calc_indices() {
    indices = {
        0, 1, 2,
        2, 3, 0,
    };
}

std::shared_ptr<shader> line::_shader = nullptr;

std::shared_ptr<shader> line::get_shader() {
    return _shader;
}

void line::bind_uniforms() {
    this->get_shader()->set_mat4("model", glm::mat4(1.0f));
    this->get_shader()->set_vec3("color", this->color);
}