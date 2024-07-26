#include "line.hpp"

line::line(
    glm::vec3 src,
    glm::vec3 dst,
    float width,
    glm::vec4 color
) : edge_component(src, dst, color), width(width) {
    init_buffers();
}

line::line(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : line(glm::vec3(src, 0.0f), glm::vec3(dst, 0.0f), width, BLACK) { }

line::line(const line & l) : edge_component(l), width(l.width) {
    init_buffers();
}

std::shared_ptr<component> line::copy() {
    return std::make_shared<line>(*this);
}

glm::vec3 line::get_center() {
    return (get_src() + get_dst()) / 2.0f;
}

float line::get_width() {
    return width;
}

void line::set_width(float width) {
    this->width = width;
}

bool line::hit(glm::vec2 pt) {
    glm::vec3 p(pt, 0.0f);
    float d = glm::length2(get_dst() - get_src());
    float t = std::min(d, std::max(0.0f, glm::dot(p - get_src(), get_dst() - get_src())));
    return glm::length((p - get_src()) * d - (get_dst() - get_src()) * t) / d <= get_width();
}

void line::drag(glm::vec2 d) {
    // this->set_src(this->get_src() + d);
    // this->set_dst(this->get_dst() + d);
}

void line::calc_vertices() {
    float dist = glm::length(get_dst() - get_src());
    glm::vec3 v = glm::normalize(get_dst() - get_src());
    if (dist == 0) v = ZERO3;
    glm::vec3 perp(v.y, -v.x, 0.0f);
    vertices = {
        get_src() + perp * (get_width() / 2), 
        get_src() - perp * (get_width() / 2),
        get_dst() - perp * (get_width() / 2),
        get_dst() + perp * (get_width() / 2),
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
    this->get_shader()->set_vec4("color", this->color);
}