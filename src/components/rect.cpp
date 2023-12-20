#include "rect.hpp"

rect::rect(
    glm::vec3 position,
    float length,
    float width,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 color
) : component(position, rotation, scale, color) {
    this->length = length;
    this->width = width;

    init_buffers();
}

rect::rect(
    glm::vec2 pos,
    float length,
    float width
) : rect(glm::vec3(pos, 0.0f), length, width, ZERO3, ONE3, BLACK) { }

float rect::get_length() const {
    return length;
}

float rect::get_width() const {
    return width;
}

void rect::set_length(float length) {
    this->length = length;
    update_vertices();
}

void rect::set_width(float width) {
    this->width = width;
    update_vertices();
}

void rect::set_square(float side) {
    this->length = side;
    this->width = side;
    update_vertices();
}

void rect::init_buffers() {
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

void rect::calc_vertices() {
    vertices = {
        {-width/2, -length/2},
        { width/2, -length/2},
        { width/2,  length/2},
        {-width/2,  length/2},
    };
}