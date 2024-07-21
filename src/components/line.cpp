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

line::line(const line & l) : edge_component(l) {
    this->width = l.width;

    init_buffers();
}

std::shared_ptr<component> line::copy() {
    return std::make_shared<line>(*this);
}

glm::vec2 line::get_center() const {
    return (src + dst) / 2.0f;
}

float line::get_width() {
    return width;
}

void line::set_width(float width) {
    this->width = width;
    this->update_vertices();
}

bool line::hit(glm::vec2 pt) {
    float d = glm::length2(dst - src);
    float t = std::min(d, std::max(0.0f, glm::dot(pt - src, dst - src)));
    return glm::length((pt - src) * d - (dst - src) * t) / d <= width;
}

void line::drag(glm::vec2 d) {
    // this->set_src(this->get_src() + d);
    // this->set_dst(this->get_dst() + d);
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