#include "rect.hpp"

rect::rect(
    glm::vec3 position = ZERO3,
    float length = 1.0,
    float width = 1.0,
    glm::vec3 rotation = ZERO3,
    glm::vec3 scale = ONE3,
    glm::vec3 color = BLACK
) : component(position, rotation, scale, color) {
    this->length = length;
    this->width = width;

    init_vertices();
}

rect::rect(
    glm::vec2 pos,
    float length = 1.0,
    float width = 1.0
) : rect(glm::vec3(pos, 0.0), length, width) { }

void rect::init_vertices() {
    glBindVertexArray(VAO);

    vertices = {
        {-width/2, -length/2},
        { width/2, -length/2},
        { width/2,  length/2},
        {-width/2,  length/2},
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices.front(), GL_STATIC_DRAW);

    indices = {
        0, 1, 2,
        2, 3, 0,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) 0);

    glBindVertexArray(0);
}