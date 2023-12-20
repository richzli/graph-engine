#include "line.hpp"

line::line(
    glm::vec2 src,
    glm::vec2 dst,
    float width,
    glm::vec3 color
) : component(ZERO3, ZERO3, ONE3, color) {
    this->src = src;
    this->dst = dst;
    this->width = width;

    init_buffers();
}

line::line(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : line(src, dst, width, BLACK) { }

glm::vec2 line::get_src() {
    return src;
}

glm::vec2 line::get_dst() {
    return dst;
}

float line::get_width() {
    return width;
}

void line::set_src(glm::vec2 src) {
    this->src = src;
    update_vertices();
}

void line::set_dst(glm::vec2 dst) {
    this->dst = dst;
    update_vertices();
}

void line::set_width(float width) {
    this->width = width;
    update_vertices();
}

void line::init_buffers() {
    glBindVertexArray(VAO);

    calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices.front(), GL_STATIC_DRAW);

    indices = {
        0, 1, 2,
        2, 3, 0,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);

    glBindVertexArray(0);
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