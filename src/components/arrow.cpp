#include "arrow.hpp"

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width,
    glm::vec3 color
) : line(src, dst, width, color) {
    init_buffers();
}

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : arrow(src, dst, width, BLACK) { }

void arrow::init_buffers() {
    glBindVertexArray(VAO);

    calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices.front(), GL_STATIC_DRAW);

    indices = {
        0, 1, 2,
        2, 6, 0,
        2, 3, 4,
        2, 4, 6,
        4, 5, 6,
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);

    glBindVertexArray(0);
}

void arrow::calc_vertices() {
    float dist = glm::length(dst - src);
    glm::vec2 v = glm::normalize(dst - src);
    if (dist == 0) v = ZERO2;
    glm::vec2 perp(v.y, -v.x);

    glm::vec2 end = dst - glm::normalize(dst - src) * (2 * width);
    glm::vec2 bgn;
    if (dist <= 2 * width) {
        bgn = end;
    } else {
        bgn = src;
    }

    vertices = {
        bgn + perp * (width/2),
        bgn - perp * (width/2),
        end - perp * (width/2),
        end - perp * width,
        dst,
        end + perp * width,
        end + perp * (width/2),
    };
}