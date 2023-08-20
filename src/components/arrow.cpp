#include "arrow.hpp"

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width = 1.0f,
    glm::vec3 color = BLACK
) : line(src, dst, width, color) {
    init_vertices();
}

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width = 1.0f
) : arrow(src, dst, width, BLACK) { }

void arrow::init_vertices() {
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
    glm::vec2 v = glm::normalize(dst - src);
    glm::vec2 perp(v.y, -v.x);
    float dist = glm::length(dst - src);

    glm::vec2 end;
    if (dist <= 4 * width) {
        end = dst - (dst - src) / 2.0f;
    } else {
        end = dst - glm::normalize(dst - src) * (width * 2);
    }

    vertices = {
        src + perp * (width/2),
        src - perp * (width/2),
        end - perp * (width/2),
        end - perp * width,
        dst,
        end + perp * width,
        end + perp * (width/2),
    };
}